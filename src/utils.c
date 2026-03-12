int is_word(char c)
{
    return(c != '\0' && c != ' ' && c != '"' && c != '\'' && c != '<' && c != '>' && c != '|' && c != '\t' && c != '\n' && c != '\v' && c != '\f' && c != '\r');
}

int is_space(char c)
{
    return(c == '\0' || c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

int is_operators(char c)
{
    return(c == '<' || c == '>' || c == '|');
}

int is_qutotes(char c)
{
    return(c == 34 || c == 39);
}