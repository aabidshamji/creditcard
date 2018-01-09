/***********************************************************************
 * Homework: Calculating Credit Card Interest
 ***********************************************************************/

#include <stdio.h>

#define YEAR 365;

// function declarations
int month (int m);
double interest (double bal, int current_month, const double apr);

int
main (void){

  // variable declarations for variables that may change
  unsigned int month_start = 9;
  double init_bal = 500;
  const double apr = 0.18;
  double payment = 35;

  // variable declarations
  double balance = init_bal;
  unsigned int cycle = 0;
  unsigned int current_month = ((month_start - 1) % 12) + 1; // val that will loop from 0-12 inclusive only
  double intrst = interest(balance, current_month, apr);
  double intrst_so_far = 0; // counter for all the interest payed

  printf("Calculating Credit Card Interest\n\nAPR: %.2lf\nInitial Balance: %.2lf\nMinimum Payment: %.2lf\n\n", apr, init_bal, payment);

  printf("Cycle	Month	Intrst	 Payment   Balance\n"); // header

  while (balance > 0.00) {

    current_month = ((month_start - 1) % 12) + 1; // find the current month
    intrst = interest(balance, current_month, apr); // find the current interest
    balance = (balance - payment) + intrst; // find the account balance

    printf("%-7d %-7d $%-7.2lf $%-8.2lf $%.2lf\n", cycle, current_month, intrst, payment, balance);

    cycle++; // increment the billing cycle
    month_start++; // increment the starting month to find the current month

    // check if the balance in greated than the min payment and adjust accordingly
    if (balance < payment) {
      payment = balance;
      balance = 0.00;
    }

    // adds the interest of this cycle to the total interst payed
    intrst_so_far += intrst;
  }

  // adjust the variables to account for the last billing cycle
  current_month = ((month_start - 1) % 12) + 1;
  intrst = interest(payment, current_month, apr);
  intrst_so_far += intrst;

  printf("%-7d %-7d $%-7.2lf $%-8.2lf $%.2lf\n", cycle, current_month, intrst, payment, balance);

  // increment the cycle to the a summary for all the past cycles
  cycle++;
  printf("After %d months, you paid $%.2lf on an intial balance of $%.2lf.\n",
        cycle, (intrst_so_far + init_bal), init_bal);

  return 0;

} // main (void)

// calculates the daily periodic rate for the given billing cycle
/*
Preconditions:
    bal must be a positive real number
    apr must be a positive real number, 0 < apr < 1
    current_month is either 28, 30, 31 and corresponding to an int between 1 and 12 inclusive
Postconditions:
    interest returns the interest accumilated for that billing cycle buy multiplying:
    daily balance * dpr * number of days in that month
    0 < rate < bal
*/
double
interest (double bal, int current_month, const double apr){

  double dpr = apr / YEAR;

  double rate = dpr * month(current_month) * bal;
  return rate;
} // interest (bal, current_month)

// interest (bal, current_month)

// month(m) - func that returns the corresponding number of days in a given month
/*
Preconditions:
    1 <= M <= 12
Postconditions:
    returns only three different values: 31 || 30 || 28
*/
int
month (int m) {
  switch (m) {
    case 4:
    case 6:
    case 9:
    case 11:
      return 30;
      break;
    case 2:
      return 28;
    default:
      return 31;
  }
} // month (m)
