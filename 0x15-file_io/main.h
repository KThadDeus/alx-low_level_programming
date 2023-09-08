#ifndef MAIN_H
#define MAIN_H

void exit_with_error(int code, const char *message);
int create_file(const char *filename, char *text_content);
int append_text_to_file(const char *filename, char *text_content);
int main(int argc, char *argv[]);
void print_error(const char *message);

#endif /* MAIN_H */
