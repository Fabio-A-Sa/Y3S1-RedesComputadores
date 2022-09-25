// Write to serial port in canonical mode
//
// Modified by: Eduardo Nuno Almeida [enalmeida@fe.up.pt]

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>

// Baudrate settings are defined in <asm/termbits.h>, which is
// included by <termios.h>
#define BAUDRATE B38400
#define _POSIX_SOURCE 1 // POSIX compliant source

#define FALSE 0
#define TRUE 1

#define BUF_SIZE 256

volatile int STOP = FALSE;

int main(int argc, char *argv[])
{
    // Program usage: Uses either COM1 or COM2
    const char *serialPortName = argv[1];

    if (argc < 2)
    {
        printf("Incorrect program usage\n"
               "Usage: %s <SerialPort>\n"
               "Example: %s /dev/ttyS1\n",
               argv[0],
               argv[0]);
        exit(1);
    }

    // Open serial port device for writing and not as controlling tty
    // because we don't want to get killed if linenoise sends CTRL-C.
    int fd = open(serialPortName, O_WRONLY | O_NOCTTY);
    if (fd < 0)
    {
        perror(serialPortName);
        exit(-1);
    }

    struct termios oldtio;
    struct termios newtio;

    // Save current port settings
    if (tcgetattr(fd, &oldtio) == -1)
    {
        perror("tcgetattr");
        exit(-1);
    }

    // Clear struct for new port settings
    memset(&newtio, 0, sizeof(newtio));

    // BAUDRATE: Set bps rate. You could also use cfsetispeed and cfsetospeed.
    // CRTSCTS : output hardware flow control
    //           ATTENTION:  only used if the cable has all necessary lines (is
    //           a null modem cable), otherwise the output flow control is set
    //           automatically by software by the driver.
    // CS8     : 8n1 (8bit,no parity,1 stopbit)
    // CLOCAL  : local connection, no modem control
    // CREAD   : enable receiving characters
    newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;

    // IGNPAR: Ignore framing and parity errors
    // ICRNL:  Map CR to NL (otherwise a CR input on the other computer
    //         will not terminate input)
    // Otherwise make device raw (no other input processing)
    newtio.c_iflag = IGNPAR | ICRNL;

    // Raw output
    newtio.c_oflag = 0;

    // ICANON : enable canonical input
    // disable all echo functionality, and don't send signals to calling program
    newtio.c_lflag = ICANON;

    // Initialize all control characters
    // default values can be found in /usr/include/termios.h, and are given
    // in the comments, but we don't need them here
    newtio.c_cc[VINTR] = 0;    // Ctrl-c
    newtio.c_cc[VQUIT] = 0;    // Ctrl-'\'
    newtio.c_cc[VERASE] = 0;   // del
    newtio.c_cc[VKILL] = 0;    // @
    newtio.c_cc[VEOF] = 4;     // Ctrl-d
    newtio.c_cc[VTIME] = 0;    // inter-character timer unused
    newtio.c_cc[VMIN] = 1;     // blocking read until 1 character arrives
    newtio.c_cc[VSWTC] = 0;    // '\0'
    newtio.c_cc[VSTART] = 0;   // Ctrl-q
    newtio.c_cc[VSTOP] = 0;    // Ctrl-s
    newtio.c_cc[VSUSP] = 0;    // Ctrl-z
    newtio.c_cc[VEOL] = 0;     // '\0'
    newtio.c_cc[VREPRINT] = 0; // Ctrl-r
    newtio.c_cc[VDISCARD] = 0; // Ctrl-u
    newtio.c_cc[VWERASE] = 0;  // Ctrl-w
    newtio.c_cc[VLNEXT] = 0;   // Ctrl-v
    newtio.c_cc[VEOL2] = 0;    // '\0'

    // Now clean the line and activate the settings for the port
    // tcflush() discards data written to the object referred  to
    // by  fd but not transmitted, or data received but not read,
    // depending on the value of queue_selector:
    //   TCIFLUSH - flushes data received but not read.
    tcflush(fd, TCIFLUSH);

    // Set new port settings
    if (tcsetattr(fd, TCSANOW, &newtio) == -1)
    {
        perror("tcsetattr");
        exit(-1);
    }

    printf("New termios structure set\n");

    // Create string to send
    unsigned char buf[BUF_SIZE] = {0};

    for (int i = 0; i < BUF_SIZE; i++)
    {
        buf[i] = 'a' + i % 26;
    }

    // In canonical mode, strings must end with '\n'
    buf[BUF_SIZE - 1] = '\n';

    int bytes = write(fd, buf, BUF_SIZE);
    printf("Bytes written = %d\n", bytes);

    // Wait until all bytes have been written to the serial port
    sleep(1);

    // Restore the old port settings
    if (tcsetattr(fd, TCSANOW, &oldtio) == -1)
    {
        perror("tcsetattr");
        exit(-1);
    }

    close(fd);

    return 0;
}
