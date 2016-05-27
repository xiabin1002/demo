/*
 * sysdep1.c	system dependant routines.
 *
 *		m_dtrtoggle	- dropt dtr and raise it again
 *		m_break		- send BREAK signal
 *		m_getdcd	- get modem dcd status
 *		m_setdcd	- set modem dcd status
 *		m_savestate	- save modem state
 *		m_restorestate	- restore saved modem state
 *		m_nohang	- tell driver not to hang up at DTR drop
 *		m_hupcl		- set hangup on close on/off
 *		m_setparms	- set speed, parity, bits and stopbits
 *		m_readchk	- see if there is input waiting.
 *		m_wait		- wait for child to finish. Sysdep. too.
 *
 *		If it's possible, Posix termios are preferred.
 *
 *		This file is part of the minicom communications package,
 *		Copyright 1991-1995 Miquel van Smoorenburg.
 *
 *		This program is free software; you can redistribute it and/or
 *		modify it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *   jl  23.06.97  adjustable DTR downtime
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "sysdep.h"
//#include "minicom.h"

/* Set hardware flow control. */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


/* Set RTS line. Sometimes dropped. Linux specific? */
static void m_setrts(int fd)
{
#ifdef USE_SOCKET
  if (portfd_is_socket)
    return;
#endif
#if defined(TIOCM_RTS) && defined(TIOCMODG)
  {
    int mcs=0;

    ioctl(fd, TIOCMODG, &mcs);
    mcs |= TIOCM_RTS;
    ioctl(fd, TIOCMODS, &mcs);
  }
#endif
}

/* Variables to save states in */
#ifdef POSIX_TERMIOS
static struct termios savetty;
static int m_word;
#else
#  if defined (_BSD43) || defined (_V7)
static struct sgttyb sg;
static struct tchars tch;
static int lsw;
static int m_word;
#  endif
#endif

/*
 * Restore the state of a port
 */
void m_restorestate(int fd)
{
#ifdef USE_SOCKET
  if (portfd_is_socket)
    return;
#endif
#ifdef POSIX_TERMIOS
  tcsetattr(fd, TCSANOW, &savetty);
#else
#  if defined(_BSD43) || defined(_V7)
  ioctl(fd, TIOCSETP, &sg);
  ioctl(fd, TIOCSETC, &tch);
#  endif
#  ifdef _BSD43
  ioctl(fd, TIOCLSET, &lsw);
#  endif
#endif
#ifdef TIOCMODS
  ioctl(fd, TIOCMODS, &m_word);
#endif
}

/*
 * Set the line status so that it will not kill our process
 * if the line hangs up.
 */
/*ARGSUSED*/
void m_nohang(int fd)
{
#ifdef USE_SOCKET
  if (portfd_is_socket)
    return;
#endif
  {
#ifdef POSIX_TERMIOS
    struct termios sgg;

    tcgetattr(fd, &sgg);
    sgg.c_cflag |= CLOCAL;
    tcsetattr(fd, TCSANOW, &sgg);
#else
#  if defined (_BSD43) && defined(LNOHANG)
    int lsw;

    ioctl(fd, TIOCLGET, &lsw);
    lsw |= LNOHANG;
    ioctl(fd, TIOCLSET, &lsw);
#  endif
#endif
  }
}

/*
 * Set hangup on close on/off.
 */
void m_hupcl(int fd, int on)
{
#ifdef USE_SOCKET
  if (portfd_is_socket)
    return;
#endif
  /* Eh, I don't know how to do this under BSD (yet..) */
#ifdef POSIX_TERMIOS
  {
    struct termios sgg;

    tcgetattr(fd, &sgg);
    if (on)
      sgg.c_cflag |= HUPCL;
    else
      sgg.c_cflag &= ~HUPCL;
    tcsetattr(fd, TCSANOW, &sgg);
  }
#endif
}

void m_sethwf(int fd, int on)
{
  struct termios tty;
  tcgetattr(fd, &tty);
  if (on)
    tty.c_cflag |= CRTSCTS;
  else
    tty.c_cflag &= ~CRTSCTS;
  tcsetattr(fd, TCSANOW, &tty);
}
/*
 * Set baudrate, parity and number of bits.
 */
void m_setparms(int fd, int baudr, char *par, int bit, int stopb,
                int hwf, int swf)
{
  int spd = -1;
  struct termios tty;
  tcgetattr(fd, &tty);

  switch (baudr) {
  case 9600:	spd = B9600;	break;
  case 19200:	spd = B19200;	break;
  case 38400:	spd = B38400;	break;
  default:	spd = B9600;	break;
  }

  if (spd != -1) {
    cfsetospeed(&tty, (speed_t)spd);
    cfsetispeed(&tty, (speed_t)spd);
  }

  switch (bit) {
    case 5:
      tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS5;
      break;
    case 6:
      tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS6;
      break;
    case 7:
      tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS7;
      break;
    case 8:
    default:
      tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
      break;
  }
  /* Set into raw, no echo mode */
  tty.c_iflag =  IGNBRK;
  tty.c_lflag = 0;
  tty.c_oflag = 0;
  tty.c_cflag |= CLOCAL | CREAD;
//#ifdef _DCDFLOW
//  tty.c_cflag &= ~CRTSCTS;
//#endif
  tty.c_cc[VMIN] = 1;
  tty.c_cc[VTIME] = 5;

  if (swf)
    tty.c_iflag |= IXON | IXOFF;
  else
    tty.c_iflag &= ~(IXON|IXOFF|IXANY);

  tty.c_cflag &= ~(PARENB | PARODD);

 if (par[0] == 1) //输入和输出是奇校验
    tty.c_cflag |= (PARENB | PARODD);
 else  if (par[0] == 2)//输入和输出是偶校验
     tty.c_cflag |= PARENB;

  if (stopb == 2)
    tty.c_cflag |= CSTOPB;
  else
    tty.c_cflag &= ~CSTOPB;

  tcsetattr(fd, TCSANOW, &tty);

  //m_setrts(fd);

  m_sethwf(fd, hwf);

}

