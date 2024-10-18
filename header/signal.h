#ifndef SIGNAL_H
# define SIGNAL_H

#include <signal.h>

extern sig_atomic_t g_sig;

void set_shell_input_sig_handler(void);

# endif