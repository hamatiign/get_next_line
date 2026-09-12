int find_newline(char *str) {
  int i = 0;
  while (str[i]) {
    if (str[i] == '\n')
      return (i);
    i++;
  }
  return (-1);
}
