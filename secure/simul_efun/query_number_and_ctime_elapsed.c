/*  -*- LPC -*-  */
/*
 * $Locker:  $
 * $Id: query_number_and_ctime_elapsed.c,v 1.3 2003/03/25 20:02:48 wodan Exp $
*/
string number_as_string(int n);

/**
 * Cotains some simul_efuns.
 * @author Pinkfish
 */
/**
 * This method turns a number into a string.  It returns a string of the
 * form "one hundred and twenty four".  This function should be used and
 * not number_as_string below.
 * The limit argument is used to set the cut off point at which it will
 * print "many".
 *
 * @param i the number to return as a string
 * @param limit the largest number to process
 * @return the number as a nice string
 */

#if !efun_defined(query_num)
string query_num(int n, int limit) {
  string ret;
  int i;

  if (limit && n>limit) return "many"; /* this is a little pointless ... */
  if (n < 0) return "many"; /* fo wraps... */
  if (n > 99999) return "many"; /* sorry 'bout the hard limit */
  ret = 0;
  if ((i = n/1000)) {
    n = n%1000;
    if (!n)
      return number_as_string(i) + " thousand";
    ret = number_as_string(i) + " thousand";
  }
  if ((i = n/100)) {
    n = n%100;
    if (ret) {
      if (!n)
        return ret + " and " + number_as_string(i) + " hundred";
      ret += ", " + number_as_string(i) + " hundred";
    } else {
      if (!n)
        return number_as_string(i) + " hundred";
      ret = number_as_string(i) + " hundred";
    }
  }
  if (ret)
    return ret + " and " + number_as_string(n);
  return number_as_string(n);
} /* query_num() */

#endif
/**
 * This method turns a number less than 100 into a string.  This function should
 * not be used.  It will only work for numbers less than 100.
 *
 * @param n the number to turn into a string
 * @return the number as a nice string
 * @see query_num()
 */
string number_as_string(int n) {
  string ret;

  if (!n) return "zero";
  if (n<20 && n>9) return ({ "ten", "eleven", "twelve", "thirteen",
                             "fourteen", "fifteen", "sixteen", "seventeen",
                             "eighteen", "nineteen" })[n-10];
  ret = ({ "", "", "twenty", "thirty", "forty", "fifty", "sixty",
           "seventy", "eighty", "ninety"})[n/10];
  if ((n = n%10)&&(ret!="")) ret += "-";
  return ret + ({ "", "one", "two", "three", "four", "five", "six",
                  "seven", "eight", "nine"})[n];
} /* number_as_string() */


/**
 * This method returns the ordinal of a number as a string (ie, "first",
 * "thirtieth", etc.)
 * @param n the number for which you want the ordinal
 * @returns the ordinal of the number as a string
 * @see query_num(), ordinal()
 */
string word_ordinal(int num)  {
   string word = "";
   int    part;

   switch (part = num % 100)  {
       case 0:
           word = "th";
           break;
       case 1 .. 12:
           word = ({
                  "first",   "second", "third", "fourth", "fifth",    "sixth",
                  "seventh", "eighth", "ninth", "tenth",  "eleventh", "twelfth"
                  })[part - 1];
           break;
 
       case 13 .. 19:
           word = query_num(num % 100, 99999) + "th";
           break;

       default:
           if (part % 10 == 0)  {
               word = ({
                      "twentieth", "thirtieth", "fortieth", "fiftieth", "sixtieth",
                      "seventieth", "eightieth", "ninetieth"
                      })[part / 10 - 2];
           }
           else  {
               word = ({
                      "twenty", "thirty", "forty", "fifty", "sixty", "seventy",
                      "eighty", "ninety"
                      })[part / 10 - 2] + "-" + word_ordinal(part % 10);
           }
           break;
    }

    num = (num / 100) * 100;
    if (num != 0)   {
        if (part > 0)  word = query_num(num, 99999) + " and " + word;
        else word = query_num(num, 99999) + word;
    }
    return word;
}
varargs string ctime_elapsed( int time_elapsed, int mode ) {
    int sec, min, hour, day;
    string seconds, minutes, hours, days; 
    string *retval;

    sec = time_elapsed % 60;
    min = (time_elapsed / 60) % 60;
    hour = (time_elapsed / (60 * 60)) % 24;
    day = time_elapsed / (60 * 60 * 24);

    if ( mode ) {
        seconds = query_num( sec, 99999 );
        minutes = query_num( min, 99999 );
        hours = query_num( hour, 99999 );
        days = query_num( day, 99999 );
    }
    else {
        seconds = sec + "";
        minutes = min + "";
        hours = hour + "";
        days = day + "";
    }

    retval = ({ });

    if (day > 0) {
        retval += ({ days + " day" });
        if (day > 1) {
            retval[<1] += "s";
        }
    }

    if (hour > 0) {
        retval += ({ hours + " hour" });
        if (hour > 1) {
            retval[<1] += "s";
        }
    }

    if (min > 0) {
        retval += ({ minutes + " minute" });
        if (min > 1) {
            retval[<1] += "s";
        }
    }

    if (sec > 0) {
        retval += ({ seconds + " second" });
        if (sec > 1) {
            retval[<1] += "s";
        }
    }

    if (sizeof(retval) == 0) {
        return "0 seconds";
    }

    if (sizeof(retval) == 1) {
        return retval[0];
    }
    return implode(retval[0..<2], ", ") + " and " + retval[<1];
} /* ctime_elapsed() */

/**
 * Convert a number into a number of times. eg. 1 = once, 2 = twice, 3 = three
 * times etc. etc.
 *
 * @param the number in question
 * @return a string equivalent.
 */
string query_times(int num) {
  string retval;
  
  switch(num) {
  case 0:
    retval = "";
    break;
  case 1:
    retval = "once";
    break;
  case 2:
    retval = "twice";
    break;
  default:
    retval = query_num(num, 0) + " times";
  }

  return retval;
}
