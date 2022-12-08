//////////////////////////////////////////////////////////////////
// @brief - writer application to replace the writer shell script
//////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <syslog.h>
#include <string.h>

#define WRITER_MAX_FILE_PATH_LEN (256)
#define WRITER_MAX_STRING_LEN (256)

int main(int argc, char** argv)
{
  int ret = 1;

  openlog("writer:", 0, 0);
  if (argc == 3 && strlen(argv[1]) <= WRITER_MAX_FILE_PATH_LEN) {
    FILE *ptr_file = fopen(argv[1], "w");
    unsigned int passed_string_len = strlen(argv[2]);
    int a ;
    if (ptr_file != NULL && passed_string_len <= WRITER_MAX_STRING_LEN) {
      if (a = fwrite(argv[2], 1, passed_string_len, ptr_file), a == passed_string_len) {
        syslog(LOG_USER, "writing %s to %s", argv[2], argv[1]);
        ret = 0;
      } else {
        syslog(LOG_ERR, "Failed to write string to file, %s, %d", argv[1], a);
      }
    } else {
      syslog(LOG_ERR, "Failed to open file %s", argv[1]);
    }

  } else {
    syslog(LOG_ERR, "Invalid arguments passed");
  }

  closelog();

  return ret;
}

