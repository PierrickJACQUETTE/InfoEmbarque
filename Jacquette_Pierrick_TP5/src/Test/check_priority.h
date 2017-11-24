//JACQUETTE Pierrick Tp5

#ifndef __CHECK_PRIORITY_H__
#define __CHECK_PRIORITY_H__

#include <check.h>
#include "../thread.h"

int nb;

/**
 * fonction permettant de creer la suite des tests a executer
 * @return  La suite de test
 */
Suite* init_suiteThread(void);

#endif
