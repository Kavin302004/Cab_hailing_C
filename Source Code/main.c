#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define YELLOW_COLOR "\033[33m"
#define BLUE_COLOR "\033[34m"
#define LIGHT_RED_COLOR "\033[91m"
#define LIGHT_GREEN_COLOR "\033[92m"
#define LIGHT_YELLOW_COLOR "\033[93m"
#define LIGHT_BLUE_COLOR "\033[94m"
#define LIGHT_MAGENTA_COLOR "\033[95m"
#define LIGHT_CYAN_COLOR "\033[96m"
#define MAGENTA_COLOR "\033[35m"
#define CYAN_COLOR "\033[36m"
#define LIGHT_GRAY_COLOR "\033[37m"

struct custonme {
  char name[100];
  char password[100];
  char place[100];
  char number[100];
} stcust[100];

struct drivern {
  char named[100];
  char passs[100];
  char placed[100];
  char carty[100];
} stdriv[100];

void printColoredText(const char *text, const char *color) {
  printf("%s%s%s", color, text, RESET_COLOR);
}

int generateOTP() {
  srand(time(NULL));
  return rand() % 1000000;
}

int isFileEmpty(const char *filename) {
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    printf("File could not be opened.\n");
    return -1;
  }

  int character = fgetc(file);

  if (character == EOF) {

    fclose(file);
    return 1;
  }

  fclose(file);
  return 0;
}

void removeStrings(char arr[][5], int rows, const char *stringToKeep) {
  int stringToKeepIndex = -1;

  for (int i = 0; i < rows; i++) {
    if (strcmp(arr[i], stringToKeep) == 0) {
      stringToKeepIndex = i;
      break;
    }
  }

  for (int i = 0; i < rows; i++) {
    if (i != stringToKeepIndex) {
      arr[i][0] = '\0';
    }
  }
}
void sortdes(int arr[], int size) {
 
    int i, j, temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {

                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void removeLinePart(const char *filename, int lineNumber,
                    const char *searchString, const char *replacement) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error opening file: %s\n", filename);
    return;
  }

  char tempFilename[] = "temp.txt";
  FILE *tempFile = fopen(tempFilename, "w");
  if (tempFile == NULL) {
    printf("Error creating temporary file.\n");
    fclose(file);
    return;
  }

  char line[256];
  int currentLineNumber = 1;

  while (fgets(line, sizeof(line), file)) {
    if (currentLineNumber == lineNumber) {
      char *foundString = strstr(line, searchString);
      if (foundString) {
        size_t foundStringLength = strlen(searchString);
        size_t lineLength = strlen(line);
        size_t part1Length = foundString - line;

        char *part2Start = foundString + foundStringLength;
        size_t part2Length = lineLength - (part2Start - line);

        char modifiedLine[256];
        strncpy(modifiedLine, line, part1Length);
        strcpy(modifiedLine + part1Length, replacement);
        strcpy(modifiedLine + part1Length + strlen(replacement), part2Start);

        fputs(modifiedLine, tempFile);
      } else {
        fputs(line, tempFile);
      }
    } else {
      fputs(line, tempFile);
    }

    currentLineNumber++;
  }

  fclose(file);
  fclose(tempFile);

  remove(filename);
  rename(tempFilename, filename);
}

void removeString(char arr[][100], int numRows, const char *stringToRemove) {
  int i, j;
  int found = 0;

  for (i = 0; i < numRows; i++) {
    if (strcmp(arr[i], stringToRemove) == 0) {
      found = 1;
      break;
    }
  }

  if (found) {

    for (j = i; j < numRows - 1; j++) {
      strcpy(arr[j], arr[j + 1]);
    }

    memset(arr[numRows - 1], 0, sizeof(arr[numRows - 1]));

  } else {
    printf("String '%s' not found in the array.\n", stringToRemove);
  }
}

void removel(const char *filename, int lineToRemove) {
  FILE *inputFile = fopen(filename, "r");
  FILE *tempFile = fopen("temp.txt", "w");

  if (inputFile == NULL || tempFile == NULL) {
    printf("Error opening file.\n");
    return;
  }

  int lineNumber = 1;
  char buffer[512];

  while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {

    if (lineNumber != lineToRemove) {
      fputs(buffer, tempFile);
    }
    lineNumber++;
  }

  fclose(inputFile);
  fclose(tempFile);

  remove(filename);

  rename("temp.txt", filename);
}

int isNumber(char s[]) {
  for (int i = 0; i < strlen(s); i++)
    if (isdigit(s[i]) == 0)
      return 0;

  return 1;
}

int main() {

  printColoredText("******************** WELCOME TO OUR CAB BOOKING SYSTEM "
                   "********************\n",
                   LIGHT_YELLOW_COLOR);
  char u[100], driverName[100];
  float dis;
  int exita = 0;
  int cdun, pn, cus = 0, x, co, mon;
  int ho;
  char ji[100] = "";
  char y[100], g[100];
  char cod[100];

  printColoredText("Are you a customer or driver: ", BLUE_COLOR);
  scanf("%s", cod);

  if (strcmp(cod, "customer") == 0) {
    char sol[100];
    printColoredText("Do you want to create an account or login: ", BLUE_COLOR);
    scanf("%s", sol);

    if (strcmp(sol, "create") == 0) {
      FILE *file = fopen("customer.txt", "a");
      char p[100], cp[100], l[100], m[100];
      printColoredText("Enter username: ", LIGHT_GREEN_COLOR);
      scanf("%s", u);
      printColoredText("Enter password: ", LIGHT_GREEN_COLOR);
      scanf("%s", p);
      printColoredText("Re-enter password: ", LIGHT_GREEN_COLOR);
      scanf("%s", cp);

      while (strcmp(cp, p) != 0) {
        printColoredText(
            "The password and re-entered password are not the same!\n",
            RED_COLOR);
        printColoredText("Enter password: ", GREEN_COLOR);
        scanf("%s", p);
        printColoredText("Re-enter password: ", GREEN_COLOR);
        scanf("%s", cp);
      }

      printColoredText("Enter location: ", LIGHT_GREEN_COLOR);
      scanf("%s", l);
      do {
        printColoredText("Enter mobile number: ", LIGHT_GREEN_COLOR);
        scanf("%s", m);
      } while (strlen(m) != 10);

      fprintf(file, "%s,%s,%s,%s,\n", u, p, l, m);
      fclose(file);
    }

    if (strcmp(sol, "login") == 0) {
      FILE *file = fopen("customer.txt", "r");
      char p[100];
      printColoredText("Enter username: ", LIGHT_CYAN_COLOR);
      scanf("%s", u);
      printColoredText("Enter password: ", LIGHT_CYAN_COLOR);
      scanf("%s", p);

      char line[256];
      int pn = 0, un = 0;

      while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (strcmp(token, u) == 0) {
          token = strtok(NULL, ",");
          if (strcmp(token, p) == 0) {
            un = 1;
            pn = 1;
            break;
          }
        }
      }

      if (pn == 1 && un == 1) {
        printf("User has logged in\n");
        cus = 1;
      } else {
        char kop[100];
        char box[100];
        printColoredText("Username or password not available\n", RED_COLOR);
        printColoredText("forgot password?: ", LIGHT_RED_COLOR);
        scanf("%s", kop);
        if (strcmp(kop, "yes") == 0) {
          FILE *fiol = fopen("customer.txt", "r");
          char jj[100], *toke;
          int teta = 0;
          while (fgets(jj, sizeof(jj), fiol)) {
            toke = strtok(jj, ",");
            teta++;
            if (strcmp(toke, u) == 0) {
              toke = strtok(NULL, ",");
              strcpy(box, toke);
              toke = strtok(NULL, ",");
              toke = strtok(NULL, ",");
              break;
            }
          }
          int x;

          x = generateOTP();
          printf("%d\n", x);
          int y;
          char pa[100], cpa[100];
          printf("Enter OTP: ");
          scanf("%d", &y);
          if (x == y) {
            printf("OTP verified!\n");
            printColoredText("Enter password: ", LIGHT_GREEN_COLOR);
            scanf("%s", pa);
            printColoredText("Re-enter password: ", LIGHT_GREEN_COLOR);
            scanf("%s", cpa);

            while (strcmp(cpa, pa) != 0) {
              printColoredText(
                  "The password and re-entered password are not the same!\n",
                  RED_COLOR);
              printColoredText("Enter password: ", GREEN_COLOR);
              scanf("%s", pa);
              printColoredText("Re-enter password: ", GREEN_COLOR);
              scanf("%s", cpa);
            }

            removeLinePart("customer.txt", teta, box, pa);

          } else {
            printf("OTP not verified!");
          }
          fclose(fiol);

        } else {
          printf("Ok");
        }
      }

      fclose(file);
    }
  }
  if (strcmp(cod, "driver") == 0) {
    char sol[100];
    printColoredText("Do you want to create an account or login: ", BLUE_COLOR);
    scanf("%s", sol);

    if (strcmp(sol, "create") == 0) {
      FILE *file = fopen("drivers.txt", "a");
      char p[100], cp[100], c[100], l[100];
      printColoredText("Enter username: ", LIGHT_GREEN_COLOR);
      scanf("%s", u);
      printColoredText("Enter password: ", LIGHT_GREEN_COLOR);
      scanf("%s", p);
      printColoredText("Re-enter password: ", LIGHT_GREEN_COLOR);
      scanf("%s", cp);

      while (strcmp(cp, p) != 0) {
        printColoredText(
            "The password and re-entered password are not the same!\n",
            RED_COLOR);
        printColoredText("Enter password: ", LIGHT_GREEN_COLOR);
        scanf("%s", p);
        printColoredText("Re-enter password: ", LIGHT_GREEN_COLOR);
        scanf("%s", cp);
      }

      printColoredText("Enter car type: ", LIGHT_GREEN_COLOR);
      scanf("%s", c);
      printColoredText("Enter location: ", LIGHT_GREEN_COLOR);
      scanf("%s", l);

      fprintf(file, "%s,%s,%s,%s,\n", u, p, l, c);
      fclose(file);
    }

    if (strcmp(sol, "login") == 0) {
      FILE *file = fopen("drivers.txt", "r");
      char p[100];
      printColoredText("Enter username: ", LIGHT_CYAN_COLOR);
      scanf("%s", u);
      printColoredText("Enter password: ", LIGHT_CYAN_COLOR);
      scanf("%s", p);

      char line[256];
      int pn = 0, un = 0;

      while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (strcmp(token, u) == 0) {
          token = strtok(NULL, ",");
          if (strcmp(token, p) == 0) {
            un = 1;
            pn = 1;
            break;
          }
        }
      }

      if (pn == 1 && un == 1) {
        printf("Driver has logged in\n");
        cus = 2;
      } else {
        printColoredText("Username or password not available\n", RED_COLOR);

        char kop[100];
        char box[100];

        printColoredText("forgot password?: ", LIGHT_RED_COLOR);
        scanf("%s", kop);

        if (strcmp(kop, "yes") == 0) {
          FILE *fiol = fopen("drivers.txt", "r");
          char jj[100], *toke;
          int teta = 0;
          while (fgets(jj, sizeof(jj), fiol)) {
            toke = strtok(jj, ",");
            teta++;
            if (strcmp(toke, u) == 0) {
              toke = strtok(NULL, ",");
              strcpy(box, toke);
              toke = strtok(NULL, ",");
              toke = strtok(NULL, ",");
              break;
            }
          }
          int x;

          x = generateOTP();
          printf("%d\n", x);
          int y;
          char pa[100], cpa[100];
          printf("Enter OTP: ");
          scanf("%d", &y);
          if (x == y) {
            printf("OTP verified!\n");
            printColoredText("Enter password: ", LIGHT_GREEN_COLOR);
            scanf("%s", pa);
            printColoredText("Re-enter password: ", LIGHT_GREEN_COLOR);
            scanf("%s", cpa);

            while (strcmp(cpa, pa) != 0) {
              printColoredText(
                  "The password and re-entered password are not the same!\n",
                  RED_COLOR);
              printColoredText("Enter password: ", GREEN_COLOR);
              scanf("%s", pa);
              printColoredText("Re-enter password: ", GREEN_COLOR);
              scanf("%s", cpa);
            }

            removeLinePart("drivers.txt", teta, box, pa);

          } else {
            printf("OTP not verified!");
          }
          fclose(fiol);
        } else {
          printf("Ok");
        }
      }

      fclose(file);
    }
  }

  if (strcmp(cod, "admin") == 0) {
    char cop[100];
    printColoredText("Enter company password: ",BLUE_COLOR);
    scanf("%s", cop);

    if (strcmp(cop, "ItzJackOrg") == 0) {
      char sol[100];
      printColoredText("Do you want to create an account or login: ",BLUE_COLOR);
      scanf("%s", sol);

      if (strcmp(sol, "create") == 0) {
        FILE *file = fopen("admin.txt", "a");
        char u[100], p[100], cp[100], l[100];
        printColoredText("Enter username: ",LIGHT_CYAN_COLOR);
        scanf("%s", u);
        printColoredText("Enter password: ",LIGHT_CYAN_COLOR);
        scanf("%s", p);
        printColoredText("Re-enter password: ",LIGHT_CYAN_COLOR);
        scanf("%s", cp);

        while (strcmp(cp, p) != 0) {
          printColoredText("The password and re-entered password are not the same!\n",RED_COLOR);
          printColoredText("Enter password: ",LIGHT_CYAN_COLOR);
          scanf("%s", p);
          printColoredText("Re-enter password: ",LIGHT_CYAN_COLOR);
          scanf("%s", cp);
        }

        printColoredText("Enter branch location: ",LIGHT_CYAN_COLOR);
        scanf("%s", l);

        fprintf(file, "%s,%s,%s,", u, p, l);
        fclose(file);
      }

      if (strcmp(sol, "login") == 0) {
        FILE *file = fopen("admin.txt", "r");
        char u[100], p[100];
        printColoredText("Enter username: ",LIGHT_GREEN_COLOR);
        scanf("%s", u);
        printColoredText("Enter password: ",LIGHT_GREEN_COLOR);
        scanf("%s", p);

        char line[256];
        int pn = 0, un = 0;

        while (fgets(line, sizeof(line), file)) {
          char *token = strtok(line, ",");
          if (strcmp(token, u) == 0) {
            token = strtok(NULL, ",");
            if (strcmp(token, p) == 0) {
              un = 1;
              pn = 1;
              break;
            }
          }
        }

        if (pn == 1 && un == 1) {
          printf("Admin has logged in\n");
          cus = 3;
        } else {
          printColoredText("Username or password not available\n",RED_COLOR);
        }

        fclose(file);
      }
    }
  }

  if (strcmp(cod, "super_admin") == 0) {
    char cop[100];
    printColoredText("Enter super admin password: ",LIGHT_CYAN_COLOR);
    scanf("%s", cop);

    if (strcmp(cop, "ItzJithu") == 0) {
      FILE *file = fopen("superadmin.txt", "r");
      char p[100];
      printColoredText("Enter password: ",LIGHT_CYAN_COLOR);
      scanf("%s", p);

      char line[256];
      int un = 0;

      while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (strcmp(token, p) == 0) {
          un = 1;
          break;
        }
      }

      if (un == 1) {
        printf("Super admin has logged in\n");
        cus = 4;
      } else {
        printf("You are not a super admin\n");
      }

      fclose(file);
    }
  }

  char dirver[][110] = {"0"};

  if (cus == 1) {
    while (strcmp(ji, "yes") != 0) {
      char custo[100];
      sprintf(custo, "%s.txt", u);
      FILE *file = fopen(custo, "a");

      int book;
      printColoredText(
          "1. Do you want to book?\n2. Want to see payment history?\n3. "
          "Give rating\n4. Want to see driver ratings?\n5. Do you want to "
          "cancel?\n6. See customer details\n7. Car Share?\n8. Quit?\n",
          LIGHT_CYAN_COLOR);
      scanf("%d", &book);

      if (book == 1) {
        char hola[100];
        FILE *fiol = fopen("customer.txt", "r");
        char jj[100], *toke;
        while (fgets(jj, sizeof(jj), fiol)) {
          toke = strtok(jj, ",");
          if (strcmp(toke, u) == 0) {
            toke = strtok(NULL, ",");
            toke = strtok(NULL, ",");
            toke = strtok(NULL, ",");
            strcpy(hola, toke);
          }
        }

        fclose(fiol);
        char loc[100], loce[100], car[100], driverLine[256], gg[100];
        printColoredText("Enter location: ", LIGHT_CYAN_COLOR);
        scanf("%s", loc);
        printColoredText("Enter destination: ", LIGHT_CYAN_COLOR);
        scanf("%s", loce);

        FILE *filed = fopen("drivers.txt", "r");
        FILE *fild = fopen("distance.txt", "r");

        int dis = 0;
        char line[256];
        char yeah[100];
        char teah[100];

        while (fgets(line, sizeof(line), fild)) {
          char *token = strtok(line, ",");
          if (strcmp(token, loc) == 0) {
            token = strtok(NULL, ",");
            if (strcmp(token, loce) == 0) {
              token = strtok(NULL, ",");
              dis = atoi(token);
              break;
            }
          }
        }

        int foul = 0;
        int poll = 0;
        printColoredText("Select car type: ", LIGHT_CYAN_COLOR);
        scanf("%s", car);

        FILE *filep = fopen("ride.txt", "a");
        fprintf(filep, "%s,", u);
        printColoredText("Do you have a preferred driver: ", LIGHT_CYAN_COLOR);
        scanf("%s", yeah);
        if (strcmp(yeah, "yes") == 0) {
          printColoredText("Enter driver name: ", LIGHT_CYAN_COLOR);
          scanf("%s", teah);
          poll = 1;
        }
        int op=0;
        printColoredText("Nearby driver details:\n", LIGHT_CYAN_COLOR);

        char gola[100];
        strcpy(gola, hola);
        char toc[100];
        strcpy(toc, loc);
        if (poll == 1) {
          while (fgets(driverLine, sizeof(driverLine), filed)) {
            char *driverToken = strtok(driverLine, ",");
            driverToken = strtok(NULL, ",");
            driverToken = strtok(NULL, ",");
            if (strcmp(driverToken, toc) == 0) {
              driverToken = strtok(NULL, ",");
              if (strcmp(driverToken, car) == 0) {
                if (strcmp(driverLine, teah) == 0) {
                  printf("Driver name: %s\n", driverLine);
                  strcpy(gg, driverLine);
                  fprintf(filep, "%s,", driverLine);
                  strcpy(dirver[foul], gg);
                  foul++;
                  op++;
                }
              }
            }
          }
        } else {
          while (fgets(driverLine, sizeof(driverLine), filed)) {
            char *driverToken = strtok(driverLine, ",");
            driverToken = strtok(NULL, ",");
            driverToken = strtok(NULL, ",");
            if (strcmp(driverToken, toc) == 0) {
              driverToken = strtok(NULL, ",");
              if (strcmp(driverToken, car) == 0) {

                printf("Driver name: %s\n", driverLine);
                strcpy(gg, driverLine);
                fprintf(filep, "%s,", driverLine);
                strcpy(dirver[foul], gg);
                foul++;
                op++;
              }
            }
          }
        }
        if(op==0) {
            printf("No Drivers available nearby , Sorry.....\n");
          return 0;
        }
        op=0;

        fprintf(filep, "%s", "2,");
        time_t tmi;
        struct tm *utcTime;
        time(&tmi);
        utcTime = gmtime(&tmi);

        printf("Time in India: %2d:%02d:%02d\n", (utcTime->tm_hour + 6) % 24,
               (utcTime->tm_min + 30) % 60, utcTime->tm_sec);
        if ((11 < ((utcTime->tm_hour + 6) % 24) &&
             (14 > ((utcTime->tm_hour + 6) % 24)))) {
          dis = dis + 100;
        } else if ((16 < ((utcTime->tm_hour + 6) % 24) &&
                    (18 > ((utcTime->tm_hour + 6) % 24)))) {
          dis = dis + 150;
        }
        fprintf(filep, "\n");
        printf("Payment amount: %.2f\n", dis * 2.5 + 100);

        char pay[100];
        char say[100];
        char hay[100];

        printColoredText("Do you want to pay? Enter 'yes' or 'no': ",
                         LIGHT_CYAN_COLOR);
        scanf("%s", pay);
        if (strcmp(pay, "yes") == 0) {
          printColoredText(
              "Do you want to pay in advance? Enter 'yes' or 'no': ",
              LIGHT_CYAN_COLOR);
          scanf("%s", say);
          if (strcmp(say, "no") == 0) {
            printColoredText(
                "Do you want to pay in onboard? Enter 'yes' or 'no': ",
                LIGHT_CYAN_COLOR);
            scanf("%s", hay);
            if (strcmp(hay, "yes") == 0) {
              printColoredText("\nNot paid, Pay when boarding\n",
                               LIGHT_CYAN_COLOR);
              char hist[100];
              int goul = 0;
              while (goul != foul) {
                sprintf(hist, "%s.txt", dirver[goul]);
                FILE *drivor = fopen(hist, "a");
                fprintf(drivor,
                        "Starting location: %s, Final location: %s, Not "
                        "Paid,%s,Phone number: %s,%s\n",
                        toc, loce, u, gola, "onboard");
                goul++;
                fclose(drivor);
              }
              fprintf(file,
                      "Starting location: %s\nFinal location: %s\nPay when "
                      "boarding\n",
                      toc, loce);

            }

            else if (strcmp(hay, "no") == 0) {
              printf("\n Payment successful!\nStarting location: %s\nFinal "
                     "location: %s\nPaid amount: %.2f\n",
                     toc, loce, dis * 2.5 + 100);
              fprintf(file,
                      "Starting location: %s\nFinal location: %s\nPaid amount: "
                      "%.2f\n",
                      toc, loce, dis * 2.5 + 100);
              rewind(filed);
              int toul = 0;
              char dorver[][110] = {"0"};
              char driverName[100];

              if (poll==1)
              {
              while (fgets(driverLine, sizeof(driverLine), filed)) {
                char *driverToken = strtok(driverLine, ",");
                driverToken = strtok(NULL, ",");
                driverToken = strtok(NULL, ",");
                if (strcmp(driverToken, toc) == 0) {
                  driverToken = strtok(NULL, ",");
                  if (strcmp(driverToken, car) == 0) {
                    if(strcmp(driverLine,teah)==0)
                    {
                    driverToken = strtok(NULL, ",");
                    strcpy(driverName, driverLine);
                    strcpy(dorver[toul], driverName);
                    toul++;
                    }
                  }
                }
              }
              }
              else
              {
                while (fgets(driverLine, sizeof(driverLine), filed)) {
                char *driverToken = strtok(driverLine, ",");
                driverToken = strtok(NULL, ",");
                driverToken = strtok(NULL, ",");
                if (strcmp(driverToken, toc) == 0) {
                  driverToken = strtok(NULL, ",");
                  if (strcmp(driverToken, car) == 0) {
                    driverToken = strtok(NULL, ",");
                    strcpy(driverName, driverLine);
                    strcpy(dorver[toul], driverName);
                    toul++;
                  }
                }
              }
              }

              FILE *driverFile;
              int rate;
              driverFile = fopen("driverRatings.txt", "a");
              fclose(driverFile);
              driverFile = fopen("driverRatings.txt", "r");
              printColoredText("Please give a rating for the driver (1-5): ",
                               LIGHT_CYAN_COLOR);
              scanf("%d", &rate);
              rewind(driverFile);
              int zoo = 0;
              while (fgets(driverLine, sizeof(driverLine), driverFile)) {
                char *driverToken = strtok(driverLine, ",");
                if (strcmp(driverToken, dorver[0]) == 0) {
                  char *driverToken = strtok(NULL, ",");
                  int rat = atoi(driverToken);
                  float rit = (rat + rate) / 2;
                  fclose(driverFile);
                  FILE *driverFile = fopen("driverRatings.txt", "a");
                  fprintf(driverFile, "%s,%.2f\n", dorver[0], rit);
                  zoo = 1;
                  FILE *driv = fopen("driverRatings.txt", "r");
                  char newta[100];
                  int gk = 0;
                  while (fgets(newta, sizeof(newta), driv)) {
                    char *drivar = strtok(newta, ",");
                    gk++;
                    if (strcmp(drivar, dorver[0]) == 0) {
                      break;
                    }
                  }
                  fclose(driv);
                  fclose(driverFile);
                  removel("driverRatings.txt", gk);
                 
                  break;
                }
              }
              if (zoo != 1) {
                FILE *driverFile = fopen("driverRatings.txt", "a");
                fprintf(driverFile, "%s,%d\n", dorver[0], rate);
                fclose(driverFile);
               
              }

              char histo[100];
              int goul = 0;

              while (goul != toul) {
                sprintf(histo, "%s.txt", dorver[goul]);
                FILE *drivor = fopen(histo, "a");
                fprintf(drivor,
                        "Starting location: %s, Final location: %s, Paid "
                        "amount: %.2f,%s,Phone number: %s,%s\n",
                        toc, loce, dis * 2.5 + 100, u, gola, "direct booking");
                goul++;
                fclose(drivor);
              }
            } else {
              printf("Ok\n");
            }
          } else {
            printColoredText("Enter Day,date[date/month/year]: ",
                             LIGHT_CYAN_COLOR);
            char day[100];
            scanf("%s", day);
            printColoredText("Enter how many days from now: ",
                             LIGHT_CYAN_COLOR);
            int date;
            scanf("%d", &date);
            printColoredText("\nPaying in advance(discount)!\n",
                             LIGHT_CYAN_COLOR);
            printf("\n Payment successful!\nStarting location: %s\nFinal "
                   "location: %s\nPaid amount: %.2f\n",
                   toc, loce, dis * 2.5 - (10 + (date * 2)));
            char hist[100];
            int goul = 0;
            while (goul != foul) {
              sprintf(hist, "%s.txt", dirver[goul]);
              FILE *drivor = fopen(hist, "a");
              fprintf(drivor,
                      "Starting location: %s, Final location: %s, Paid advance "
                      "payment amount: %.2f,%s,Phone number: %s, Date and Day "
                      "of booking: %s\n",
                      toc, loce, 2.5 * dis - (10 + (date * 2)), u, gola, day);
              goul++;
              fclose(drivor);
            }
            fprintf(file,
                    "Starting location: %s\nFinal location: %s\nPaid advance "
                    "payment amount: %.2f\nDate and Day of booking: %s\n",
                    toc, loce, 2.5 * dis - (100 + (date * 2)), day);
          }
        } else {
          printColoredText("\nPayment cancelled!\n", LIGHT_RED_COLOR);
          fprintf(file, "Payment cancelled!\n");
          FILE *rodeo = fopen("ride.txt", "r");
        char rekka[500];
        int ash = 0;
        while (fgets(rekka, sizeof(rekka), rodeo)) {
          char *tooken = strtok(rekka, ",");
          if (strcmp(tooken, u)) {
            ash++;
          }
        }
        rewind(rodeo);
        int folder = 0, misty = 0;
        char mammoth[500];
        while (fgets(mammoth, sizeof(mammoth), rodeo)) {
          folder++;
          char *told = strtok(mammoth, ",");
          if (strcmp(told, u)) {
            misty++;
            if (misty == ash) {
              break;
            }
          }
        }
        fclose(rodeo);

        removel("ride.txt", folder);
        }

        fclose(filep);
        fclose(filed);
        fclose(fild);
      }

      if (book == 2) {
        char c;
        FILE *payfile = fopen(custo, "r");
        while ((c = getc(payfile)) != EOF) {
          printf("%c", c);
        }
        fclose(payfile);
      }

      if (book == 3) {
        FILE *driverFile = fopen("driverRatings.txt", "r");
        char driverRatingLine[256];
        char drive[100];
        char driverLine[256];
        int rate;
        printf("Driver ratings:\n");

        while (fgets(driverRatingLine, sizeof(driverRatingLine), driverFile)) {
          char *driverToken = strtok(driverRatingLine, ",");
          char *ratingToken = strtok(NULL, ",");
          printf("Driver: %s, Rating: %s\n", driverToken, ratingToken);
        }
        printColoredText("Enter driver name: ", LIGHT_CYAN_COLOR);
        scanf("%s", drive);
        printColoredText("Please give a rating for the driver (1-5): ",
                         LIGHT_CYAN_COLOR);
        scanf("%d", &rate);
        rewind(driverFile);
        int zoo = 0;
        while (fgets(driverLine, sizeof(driverLine), driverFile)) {
          char *driverToken = strtok(driverLine, ",");
          if (strcmp(driverToken, drive) == 0) {
            char *driverToken = strtok(NULL, ",");
            int rat = atoi(driverToken);
            float rit = (rat + rate) / 2;

            FILE *driveFile = fopen("driverRatings.txt", "a");
            fprintf(driveFile, "%s,%.2f\n", drive, rit);
            zoo = 1;
            fclose(driveFile);
            FILE *driv = fopen("driverRatings.txt", "r");
            char newta[100];
            int gk = 0;
            while (fgets(newta, sizeof(newta), driv)) {
              char *drivar = strtok(newta, ",");
              gk++;
              if (strcmp(drivar, drive) == 0) {
                break;
              }
            }
            fclose(driv);

            removel("driverRatings.txt", gk);

            break;
          }
        }
        if (zoo != 1) {
          FILE *driveFile = fopen("driverRatings.txt", "a");
          fprintf(driveFile, "%s,%d\n", drive, rate);
          fclose(driveFile);
        }
        fclose(driverFile);
      }

      if (book == 4) {
        FILE *driverFile = fopen("driverRatings.txt", "r");
        char driverRatingLine[256];
        char driverName[100];
        printColoredText("Enter driver name: ", LIGHT_CYAN_COLOR);
        scanf("%s", driverName);
        int ratingAvailable = 0;

        while (fgets(driverRatingLine, sizeof(driverRatingLine), driverFile)) {
          char *driverToken = strtok(driverRatingLine, ",");
          if (strcmp(driverToken, driverName) == 0) {
            char *ratingToken = strtok(NULL, ",");
            printf("Driver: %s, Rating: %s\n", driverToken, ratingToken);
            ratingAvailable = 1;
          }
        }

        if (!ratingAvailable) {
          printf("No ratings available for the driver\n");
        }

        fclose(driverFile);
      }
      if (book == 5) {
        char old[][100] = {"0"};
        int goal = 0;
        char kon[100];
        char chara;
        FILE *ridefile = fopen("ride.txt", "r");
        char new[500], his[100], *driver;
        while (fgets(new, sizeof(new), ridefile)) {
          goal = 0;
          char *driverToke = strtok(new, ",");
          if (strcmp(driverToke, u) == 0) {
            driver = strtok(NULL, ",");
            while (isNumber(driver) == 0) {
              strcpy(old[goal], driver);
              driver = strtok(NULL, ",");
              goal++;
            }
          }
        }

        int gogo = 0;

        while (gogo != goal) {
          printf("Driver: %s\n", old[gogo]);
          sprintf(his, "%s.txt", old[gogo]);
          FILE *fileo = fopen(his, "r");
          int filo = 0, kilo = 0, tk = 0;
          char few[500], dew[500];
          while (fgets(few, sizeof(few), fileo)) {
            char *driverTokeo = strtok(few, ",");
            char *drivero = strtok(NULL, ",");
            drivero = strtok(NULL, ",");
            if (strcmp(drivero, u) == 0) {
              filo = filo + 1;
            }
          }
          rewind(fileo);

          while (fgets(dew, sizeof(dew), fileo)) {
            char *driverTokeo = strtok(dew, ",");
            char *drivero = strtok(NULL, ",");
            drivero = strtok(NULL, ",");
            strcpy(kon, drivero);
            drivero = strtok(NULL, ",");
            kilo = kilo + 1;
            if (strcmp(drivero, u) == 0) {
              tk = tk + 1;
              if (tk == filo) {
                break;
              }
            }
          }
          fclose(fileo);
          removel(his, kilo);
          gogo++;
        }
        printf("%s\n", kon);
        printf("Fee deducted: 200\n");
        printf("Booking cancelled successfully!\n");
        char hix[100];
        sprintf(hix, "%s.txt", u);
        FILE *fin = fopen(hix, "a");
        fprintf(fin, "Booking Cancelled!\n");
        fclose(fin);
        fclose(ridefile);
        FILE *rodeo = fopen("ride.txt", "r");
        char rekka[500];
        int ash = 0;
        while (fgets(rekka, sizeof(rekka), rodeo)) {
          char *tooken = strtok(rekka, ",");
          if (strcmp(tooken, u)) {
            ash++;
          }
        }
        rewind(rodeo);
        int folder = 0, misty = 0;
        char mammoth[500];
        while (fgets(mammoth, sizeof(mammoth), rodeo)) {
          folder++;
          char *told = strtok(mammoth, ",");
          if (strcmp(told, u)) {
            misty++;
            if (misty == ash) {
              break;
            }
          }
        }
        fclose(rodeo);

        removel("ride.txt", folder);
      }

      if (book == 6) {

        FILE *notof = fopen("customer.txt", "r");
        char driveri[500];
        int seeka = 0;
        while (fgets(driveri, sizeof(driveri), notof)) {
          char *driverToken = strtok(driveri, ",");
          char *ratingToken = strtok(NULL, ",");
          char *hi = strtok(NULL, ",");
          char *hoi = strtok(NULL, ",");
          strcpy(stcust[seeka].name, driverToken);
          strcpy(stcust[seeka].password, ratingToken);
          strcpy(stcust[seeka].place, hi);
          strcpy(stcust[seeka].number, hoi);
          seeka++;
        }
        char dojo[100];
        printf("Do you want to see for a customer[Enter yes] or yours[Enter "
               "mine]: ");
        scanf("%s", dojo);
        if (strcmp(dojo, "yes") == 0) {
         char sendor[100];
          printf("Enter customer name: ");
          scanf("%s",sendor);
          for (int ikki = 0; ikki < seeka; ikki++) {
            if (strcmp(stcust[ikki].name,sendor)==0)
            {
            printf("%s,%s,\n", stcust[ikki].name,stcust[ikki].number);
            }
          }
        } else {
          for (int ikki = 0; ikki < seeka; ikki++) {
            if (strcmp(stcust[ikki].name, u) == 0) {
              printf("%s,%s,%s,%s,\n", stcust[ikki].name, stcust[ikki].password,
                     stcust[ikki].place, stcust[ikki].number);
            }
          }
        }
        fclose(notof);
      }

      if (book == 7) {
        FILE *yoho = fopen("carshare.txt", "a");
        fclose(yoho);
        int check = isFileEmpty("carshare.txt");

        if (check == 1) {

          FILE *zehaha = fopen("carshare.txt", "a");
          char startplace[100], destinat[100];
          printColoredText("Enter starting location: ", LIGHT_CYAN_COLOR);
          scanf("%s", startplace);
          printColoredText("Enter destination: ", LIGHT_CYAN_COLOR);
          scanf("%s", destinat);
          fprintf(zehaha, "%s,%s,%s,\n", u, startplace, destinat);
        } else {
          FILE *yohoho = fopen("carshare.txt", "r");
          char vot;
          char itsme[100];
          int see=1;

          printf("%d) ",see);
          while ((vot = getc(yohoho)) != EOF) {
           
            printf("%c", vot);
            if (vot=='\n')
            {
              see++;
              printf("%d) ",see);
            }
          }
          fclose(yohoho);
          printf("\n");
          int jolly;
          char sandy[100];
          printColoredText("Is there a person who can share ride to same location as you in this file:(yes or no)", LIGHT_CYAN_COLOR);
          scanf("%s",sandy);
          if (strcmp(sandy,"yes")==0)
          {
          printColoredText("Enter line number: ", LIGHT_CYAN_COLOR);
          scanf("%d", &jolly);
          char startplace[100], destinat[100], cartyp[100], phonum[100];
          printColoredText("Enter starting location: ", LIGHT_CYAN_COLOR);
          scanf("%s", startplace);
          printColoredText("Enter destination: ", LIGHT_CYAN_COLOR);
          scanf("%s", destinat);
          printColoredText("Enter car type: ", LIGHT_CYAN_COLOR);
          scanf("%s", cartyp);
            do{
          printColoredText("Enter phone number: ", LIGHT_CYAN_COLOR);
          scanf("%s", phonum);
            }while(strlen(phonum)!=10);

          FILE *jango = fopen("distance.txt", "r");
          char newta[500];
          int chris;
          while (fgets(newta, sizeof(newta), jango)) {
            char *token = strtok(newta, ",");
            if (strcmp(token, startplace) == 0) {
              token = strtok(NULL, ",");
              if (strcmp(token, destinat) == 0) {
                token = strtok(NULL, ",");
                chris = atoi(token);
                break;
              }
            }
          }
          fclose(jango);

          FILE *zeha = fopen("carshare.txt", "r");
          char driverone[500];
          int seem = 0;
          while (fgets(driverone, sizeof(driverone), zeha)) {
            char *driverToken = strtok(driverone, ",");
            char *ratingToken = strtok(NULL, ",");
            char *hi = strtok(NULL, ",");

            seem++;
            if (seem == jolly) {
              strcpy(itsme, driverToken);
            }
          }
          removel("carshare.txt", jolly);
          fclose(zeha);
          printf("Amount to pay: %.2f\n", (((2.5 * chris) + 100) / 2) + 50);

          printf("\n Payment successful!\nStarting location: %s\nFinal "
                 "location: %s\nPaid amount: %.2f\n",
                 startplace, destinat, (((2.5 * chris) + 100) / 2) + 50);
          fprintf(file,
                  "Starting location: %s\nFinal location: %s\nPaid amount: "
                  "%.2f\n",
                  startplace, destinat, (((2.5 * chris) + 100) / 2) + 50);
          char kairu[100];
          sprintf(kairu, "%s.txt", itsme);
          FILE *goodra = fopen(kairu, "a");
          fprintf(goodra,
                  "Starting location: %s\nFinal location: %s\nPaid amount: "
                  "%.2f\n",
                  startplace, destinat, (((2.5 * chris) + 100) / 2) + 50);
          fclose(goodra);
          FILE *filep = fopen("ride.txt", "a");
          fprintf(filep, "%s,", u);

          printColoredText("Nearby driver details: \n", LIGHT_CYAN_COLOR);
          FILE *fileon = fopen("drivers.txt", "r");
          int toul = 0;
          char drivermane[500];
          char dorver[][110] = {"0"};
          char driverName[100];
          while (fgets(drivermane, sizeof(drivermane), fileon)) {
            char *driverToken = strtok(drivermane, ",");
            driverToken = strtok(NULL, ",");
            driverToken = strtok(NULL, ",");
            if (strcmp(driverToken, startplace) == 0) {
              driverToken = strtok(NULL, ",");
              if (strcmp(driverToken, cartyp) == 0) {
                driverToken = strtok(NULL, ",");
                strcpy(driverName, drivermane);
                strcpy(dorver[toul], driverName);
                printf("Driver: %s\n", dorver[toul]);
                fprintf(filep, "%s,", dorver[toul]);
                toul++;
              }
            }
          }
          fprintf(filep, "2,\n");
          fclose(filep);
          fclose(fileon);
          FILE *driverFile;
          int rate;
          driverFile = fopen("driverRatings.txt", "a");
          fclose(driverFile);
          driverFile = fopen("driverRatings.txt", "r");
          printColoredText("Please give a rating for the driver (1-5): ",
                           LIGHT_CYAN_COLOR);
          scanf("%d", &rate);
          rewind(driverFile);
          int zoo = 0;
          while (fgets(drivermane, sizeof(drivermane), driverFile)) {
            char *driverToken = strtok(drivermane, ",");
            if (strcmp(driverToken, dorver[0]) == 0) {
              char *driverToken = strtok(NULL, ",");
              int rat = atoi(driverToken);
              float rit = (rat + rate) / 2;
              fclose(driverFile);
              FILE *driverFile = fopen("driverRatings.txt", "a");
              fprintf(driverFile, "%s,%.2f\n", dorver[0], rit);
              zoo = 1;
              FILE *driv = fopen("driverRatings.txt", "r");
              char newta[100];
              int gk = 0;
              while (fgets(newta, sizeof(newta), driv)) {
                char *drivar = strtok(newta, ",");
                gk++;
                if (strcmp(drivar, dorver[0]) == 0) {
                  break;
                }
              }
              fclose(driv);
              fclose(driverFile);

              removel("driverRatings.txt", gk);
              break;
            }
          }
          if (zoo != 1) {
            FILE *driverFile = fopen("driverRatings.txt", "a");
            fprintf(driverFile, "%s,%d\n", dorver[0], rate);
            fclose(driverFile);
          }

          char histo[100];
          int goul = 0;

          while (goul != toul) {
            sprintf(histo, "%s.txt", dorver[goul]);
            FILE *drivor = fopen(histo, "a");
            fprintf(drivor,
                    "Starting location: %s, Final location: %s, Paid "
                    "amount: %.2f,%s,Phone number: %s,%s\n",
                    startplace, destinat, (((2.5 * chris) + 100) / 2) + 50, u,
                    phonum, itsme);
            goul++;
            fclose(drivor);
          }
        }
          else
          {
            printf("OK!\n");
          }
        }
      }

      if (book == 8) {
        strcpy(ji, "yes");
        exita = 1;
      }
      fclose(file);
      if (exita == 0) {
        printColoredText("Do you want to end? Enter 'yes' or 'no': ",
                         LIGHT_MAGENTA_COLOR);
        scanf("%s", ji);
      }
    }
  }

  if (cus == 2) {
    while (strcmp(ji, "yes") != 0) {
      char custo[100];
      sprintf(custo, "%s.txt", u);
      FILE *file = fopen(custo, "a");

      int book;
      printColoredText("1. Do you want to see the customer queue\n2. Do you "
                       "want to see ratings\n3. Check rating\n4. check driver details?\n5. Quit?\n",
                       LIGHT_GREEN_COLOR);
      scanf("%d", &book);

      if (book == 1) {
        int b=0;
        int owl = 0;
        char driveri[500];
        FILE *payfile = fopen(custo, "r");
        while (fgets(driveri, sizeof(driveri), payfile)) {
          char *driverToken = strtok(driveri, ",");
          char *ratingToken = strtok(NULL, ",");
          char *hi = strtok(NULL, ",");
          char *hoi = strtok(NULL, ",");
          char *hoiy = strtok(NULL, ",");
          char *hoit = strtok(NULL, ",");
          owl++;
          printf("%d)%s,%s,%s,%s,%s,%s\n", owl, driverToken, ratingToken, hi,
                 hoi, hoiy, hoit);
          b++;
        }
        char ggo[100], fin[100];
        int gk;
        char gu[100], tok[100], hoal[100];
        char phon[100];
        if(b==0) {
          printf("No customers requested for cab in this area, Sorry....\n");
          return 0;
        }
        printColoredText("Do you want to pick up a customer?: ",
                         LIGHT_GREEN_COLOR);
        scanf("%s", ggo);
        fclose(payfile);

        if (strcmp(ggo, "yes") == 0) {
          printColoredText("Enter line number: ", LIGHT_GREEN_COLOR);
          scanf("%d", &gk);
          printColoredText("Enter name of person to pick: ", LIGHT_GREEN_COLOR);
          scanf("%s", gu);
          printColoredText("Enter starting location: ", LIGHT_GREEN_COLOR);
          scanf("%s", tok);
          printColoredText("Enter destination: ", LIGHT_GREEN_COLOR);
          scanf("%s", hoal);

          sprintf(fin, "%s.txt", u);
          removel(fin, gk);
          char feel[100];

          char old[][100] = {"0"};
          int goal = 0;
          char kon[100];
          char chara;
          FILE *ridefile = fopen("ride.txt", "r");
          char new[500], his[100], *driver;
          while (fgets(new, sizeof(new), ridefile)) {
            goal = 0;
            char *driverToke = strtok(new, ",");
            if (strcmp(driverToke, gu) == 0) {
              driver = strtok(NULL, ",");
              while (isNumber(driver) == 0) {
                strcpy(old[goal], driver);
                driver = strtok(NULL, ",");
                goal++;
              }
            }
          }
          char koko[100];
          char loke[100];
          char nama[100];
          strcpy(koko, hoal);
          strcpy(loke, tok);
          strcpy(nama, gu);

          removeString(old, goal, u);
          goal = goal - 1;
          int gogo = 0;

          while (gogo != goal) {
            printf("other driver: %s\n", old[gogo]);
            sprintf(his, "%s.txt", old[gogo]);
            FILE *fileo = fopen(his, "r");
            int filo = 0, kilo = 0, tk = 0;
            char few[500], dew[500];
            while (fgets(few, sizeof(few), fileo)) {
              char *driverTokeo = strtok(few, ",");
              char *drivero = strtok(NULL, ",");
              drivero = strtok(NULL, ",");
              if (strcmp(drivero, nama) == 0) {
                filo = filo + 1;
              }
            }
            rewind(fileo);

            while (fgets(dew, sizeof(dew), fileo)) {
              char *driverTokeo = strtok(dew, ",");
              char *drivero = strtok(NULL, ",");
              drivero = strtok(NULL, ",");
              strcpy(kon, drivero);
              drivero = strtok(NULL, ",");
              kilo = kilo + 1;
              if (strcmp(drivero, nama) == 0) {
                tk = tk + 1;
                if (tk == filo) {
                  break;
                }
              }
            }
            fclose(fileo);
            removel(his, kilo);
            gogo++;
          }

          FILE *fool = fopen("drivers.txt", "r");

          char fnew[500];
          int bee = 0;
          while (fgets(fnew, sizeof(fnew), fool)) {
            char *ftoke = strtok(fnew, ",");
            bee++;
            if (strcmp(ftoke, u) == 0) {
              break;
            }
          }
          removeLinePart("drivers.txt", bee, loke, koko);

          fclose(fool);

          char isoka[100];
          sprintf(isoka, "%s.txt", nama);
          FILE *goat = fopen(isoka, "a");

          do {
            printColoredText("Enter your phone number: ", LIGHT_GREEN_COLOR);
            scanf("%s", phon);
          } while (strlen(phon) != 10);

          fprintf(goat, "Driver %s has been assigned, driver number: %s\n", u,
                  phon);
          fclose(goat);
          FILE *rodeo = fopen("ride.txt", "r");
        char rekka[500];
        int ash = 0;
        while (fgets(rekka, sizeof(rekka), rodeo)) {
          char *tooken = strtok(rekka, ",");
          if (strcmp(tooken, u)) {
            ash++;
          }
        }
        rewind(rodeo);
        int folder = 0, misty = 0;
        char mammoth[500];
        while (fgets(mammoth, sizeof(mammoth), rodeo)) {
          folder++;
          char *told = strtok(mammoth, ",");
          if (strcmp(told, u)) {
            misty++;
            if (misty == ash) {
              break;
            }
          }
        }
        fclose(rodeo);

        removel("ride.txt", folder);

        }
        else
        {
          printf("Customer not picked!\n");
        }
      }

      if (book == 2) {
        FILE *driverFile = fopen("driverRatings.txt", "r");
        char driverRatingLine[256];
        printColoredText("Driver ratings:\n", LIGHT_GREEN_COLOR);

        while (fgets(driverRatingLine, sizeof(driverRatingLine), driverFile)) {
          char *driverToken = strtok(driverRatingLine, ",");
          char *ratingToken = strtok(NULL, ",");
          printf("Driver: %s, Rating: %s\n", driverToken, ratingToken);
        }

        fclose(driverFile);
      }

      if (book == 3) {
        FILE *driverFile = fopen("driverRatings.txt", "r");
        char driverRatingLine[256];
        char driverName[100];
        printColoredText("Enter driver name: ", LIGHT_GREEN_COLOR);
        scanf("%s", driverName);
        int ratingAvailable = 0;

        while (fgets(driverRatingLine, sizeof(driverRatingLine), driverFile)) {
          char *driverToken = strtok(driverRatingLine, ",");
          if (strcmp(driverToken, driverName) == 0) {
            char *ratingToken = strtok(NULL, ",");
            printf("Driver: %s, Rating: %s\n", driverToken, ratingToken);
            ratingAvailable = 1;
          }
        }

        if (!ratingAvailable) {
          printf("No ratings available for the driver\n");
        }

        fclose(driverFile);
      }

      if (book == 4) {

        FILE *notof = fopen("drivers.txt", "r");
        char driveri[500];
        int seeka = 0;
        while (fgets(driveri, sizeof(driveri), notof)) {
          char *driverToken = strtok(driveri, ",");
          char *ratingToken = strtok(NULL, ",");
          char *hi = strtok(NULL, ",");
          char *hoi = strtok(NULL, ",");
          strcpy(stdriv[seeka].named, driverToken);
          strcpy(stdriv[seeka].passs, ratingToken);
          strcpy(stdriv[seeka].placed, hi);
          strcpy(stdriv[seeka].carty, hoi);
          seeka++;
        }
        char dojo[100];
        printf("Do you want to see yours[Enter "
               "mine]: ");
        scanf("%s", dojo);
        if (strcmp(dojo, "mine") == 0) {
          for (int ikki = 0; ikki < seeka; ikki++) {
            if (strcmp(stdriv[ikki].named, u) == 0) {
              printf("%s,%s,%s,%s,\n", stdriv[ikki].named, stdriv[ikki].passs,
                     stdriv[ikki].placed, stdriv[ikki].carty);
            }
          }
        }
        fclose(notof);
      }

      if (book == 5) {
        strcpy(ji, "yes");
        exita = 1;
      }

      if (exita == 0) {
        printColoredText("Do you want to end? Enter 'yes' or 'no': ",
                         LIGHT_MAGENTA_COLOR);
        scanf("%s", ji);
      }
    }
  }

  if (cus == 4) {
    while (strcmp(ji, "yes") != 0) {
      char custo[100];
      sprintf(custo, "%s.txt", u);
      FILE *file = fopen(custo, "a");

      int book;
      printColoredText("1. Want to see driver details?\n2. Want to see customer "
             "details?\n3. Want to see specific driver history?\n4. Want to "
             "see customer payment history?\n5. Want to see driver "
             "ratings?\n6. Want to see ride deatils?\n",GREEN_COLOR);
      scanf("%d", &book);

      if (book == 4) {
        char c;
        char cust[100], na[100];
        printColoredText("Enter customer name:",GREEN_COLOR);
        scanf("%s", na);
        sprintf(cust, "%s.txt", na);
        FILE *payfile = fopen(cust, "r");
        while ((c = getc(payfile)) != EOF) {
          printf("%c", c);
        }
        fclose(payfile);
      }
      if (book == 3) {
        char c;
        char cust[100], na[100];
        printColoredText("Enter driver name:",GREEN_COLOR);
        scanf("%s", na);
        sprintf(cust, "%s.txt", na);
        FILE *payfile = fopen(cust, "r");
        while ((c = getc(payfile)) != EOF) {
          printf("%c", c);
        }
        fclose(payfile);
      }
      if (book == 1) {
        char c;
        FILE *payfile = fopen("drivers.txt", "r");
        while ((c = getc(payfile)) != EOF) {
          printf("%c", c);
        }
        fclose(payfile);
      }
      if (book == 6) {
        char c;
        FILE *payfile = fopen("ride.txt", "r");
        while ((c = getc(payfile)) != EOF) {
          printf("%c", c);
        }
        fclose(payfile);
      }
      if (book == 2) {
        char c;
        FILE *payfile = fopen("customer.txt", "r");
        while ((c = getc(payfile)) != EOF) {
          printf("%c", c);
        }
        fclose(payfile);
      }
      if (book == 5) {
        FILE *driverFile = fopen("driverRatings.txt", "r");
        char driverRatingLine[256];
        char driverName[100];
        printColoredText("Enter driver name: ",GREEN_COLOR);
        scanf("%s", driverName);
        int ratingAvailable = 0;

        while (fgets(driverRatingLine, sizeof(driverRatingLine), driverFile)) {
          char *driverToken = strtok(driverRatingLine, ",");
          if (strcmp(driverToken, driverName) == 0) {
            char *ratingToken = strtok(NULL, ",");
            printf("Driver: %s, Rating: %s\n", driverToken, ratingToken);
            ratingAvailable = 1;
          }
        }

        if (!ratingAvailable) {
          printf("No ratings available for the driver\n");
        }

        fclose(driverFile);
      }

      fclose(file);
      printColoredText("Do you want to end? Enter 'yes' or 'no': ",LIGHT_MAGENTA_COLOR);
      scanf("%s", ji);
    }
  }
  if (cus == 3) {
    while (strcmp(ji, "yes") != 0) {
      char custo[100];
      sprintf(custo, "%s.txt", u);
      FILE *file = fopen(custo, "a");

      int book;
      printColoredText(
          "1. Want to see driver details?\n2. Want to see driver ratings?\n",LIGHT_GRAY_COLOR);
      scanf("%d", &book);

      if (book == 1) {
        char c;
        FILE *payfile = fopen("drivers.txt", "r");
        while ((c = getc(payfile)) != EOF) {
          printf("%c", c);
        }
        fclose(payfile);
      }

      if (book == 2) {
        FILE *driverFile = fopen("driverRatings.txt", "r");
        char driverRatingLine[256];
        char driverName[100];
        printColoredText("Enter driver name: ",LIGHT_GRAY_COLOR);
        scanf("%s", driverName);
        int ratingAvailable = 0;

        while (fgets(driverRatingLine, sizeof(driverRatingLine), driverFile)) {
          char *driverToken = strtok(driverRatingLine, ",");
          if (strcmp(driverToken, driverName) == 0) {
            char *ratingToken = strtok(NULL, ",");
            printf("Driver: %s, Rating: %s\n", driverToken, ratingToken);
            ratingAvailable = 1;
          }
        }

        if (!ratingAvailable) {
          printf("No ratings available for the driver\n");
        }

        fclose(driverFile);
      }

      fclose(file);
      printColoredText("Do you want to end? Enter 'yes' or 'no': ",LIGHT_MAGENTA_COLOR);
      scanf("%s", ji);
    }
  }
char totod[500];
  char gold[][100]={"0"};
  int tinga[500];
  char goda[100];
  int jike=0;
  int spike=0;
  FILE *pikachu = fopen("driverRatings.txt","r");
  while(fgets(totod,sizeof(totod),pikachu))
    {
      spike++;
      char *dongle = strtok(totod,",");
      char *masta = strtok(NULL,",");
      if (atoi(masta)<3)
      {
        strcpy(gold[jike],dongle);
        sprintf(goda,"%d",spike);
        tinga[jike] = atoi(goda);
        jike++;
      }
    }
  fclose(pikachu);

  sortdes(tinga,jike);
 
  for (int songa=0;songa<jike;songa++)
    {
     removel("driverRatings.txt",tinga[songa]);
    }
 
  FILE *pasta =fopen("drivers.txt","r");
  char chocho[500];
  char rocky[100];
  int tingo[500];
  int trigger=0;
 
  for (int zeng=0;zeng<jike;zeng++)
    {
      int mingo=0;
      rewind(pasta);
  while(fgets(chocho,sizeof(chocho),pasta))
    {
      mingo++;
      char *more =strtok(chocho,",");
      if (strcmp(more,gold[zeng])==0)
      {
        sprintf(rocky,"%d",mingo);
        tingo[trigger] = atoi(rocky);
        trigger++;
      }
    }
    }
  fclose(pasta);

  sortdes(tingo,trigger);
 
  for (int pingu=0;pingu<trigger;pingu++)
    {
      removel("drivers.txt",tingo[pingu]);
    }
 
  return 0;
}