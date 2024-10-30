/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:31:42 by emorales          #+#    #+#             */
/*   Updated: 2024/10/30 18:01:25 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Função para verificar se há parênteses não balanceados
bool parentheses_checker(const char *input)
{
    int parentheses = 0;
    int i = 0;

    while (input[i])
    {
        if (input[i] == '(')
            parentheses++;
        else if (input[i] == ')')
        {
            if (parentheses == 0) // Fechamento sem abertura correspondente
                return false;
            parentheses--;
        }
        i++;
    }
    return (parentheses == 0); // Retorna true se todos os parênteses estão balanceados
}

// Função para verificar se as aspas estão balanceadas
bool quote_checker(const char *input)
{
    int i = 0;
    bool in_quotes = false;
    char quote_type = 0;

    while (input[i])
    {
        if (input[i] == '"' || input[i] == '\'')
        {
            if (!in_quotes)
            {
                in_quotes = true;
                quote_type = input[i];
            }
            else if (quote_type == input[i])
            {
                in_quotes = false;
                quote_type = 0;
            }
        }
        i++;
    }
    return !in_quotes; // Retorna true se todas as aspas estão balanceadas
}

// Função para verificar operadores mal posicionados no início/fim
bool invalid_input_checker(const char *input)
{
    int i = 0;

    if (input[i] == '|' || input[i] == '&') // Checa se o primeiro caractere é um operador inválido
        return false;

    while (input[i + 1])
    {
        if ((input[i] == '|' || input[i] == '&') && input[i + 1] == '\0')
            return false; // Checa se o último caractere é um operador inválido
        i++;
    }
    return true; // Retorna true se não há operadores mal posicionados
}

// Função para verificar redirecionamento sem arquivo
bool redirection_checker(const char *input)
{
    int i = 0;
    while (input[i])
    {
        if (input[i] == '>' || input[i] == '<')
        {
            i++;
            while (input[i] == ' ') i++; // Pula espaços após o operador
            if (input[i] == '>' || input[i] == '<' || input[i] == '|' || input[i] == '\0')
                return false; // Sem arquivo após redirecionamento ou seguido por operador inválido
        }
        i++;
    }
    return true;
}

// Função para verificar pipes sem comandos em um ou ambos os lados
bool pipe_checker(const char *input)
{
    int i = 0;
    bool previous_was_pipe = false;

    while (input[i])
    {
        if (input[i] == '|')
        {
            if (previous_was_pipe) // Verifica sequência de pipes (ex: "||")
                return false;

            // Checa se é o início ou fim do comando
            if (i == 0 || input[i + 1] == '\0')
                return false;

            previous_was_pipe = true;
        }
        else if (input[i] != ' ')
        {
            previous_was_pipe = false;
        }
        i++;
    }
    return true;
}

// Função para verificar operadores múltiplos incorretos (ex: ||| ou >>|)
bool multiple_operator_checker(const char *input)
{
    int i = 0;
    while (input[i])
    {
        if ((input[i] == '|' || input[i] == '>') && input[i] == input[i + 1] && input[i + 1] == input[i + 2])
            return false; // Detecta operadores como "|||" ou ">>>"

        if (input[i] == '>' && input[i + 1] == '|' )
            return false; // Detecta ">|"
        
        i++;
    }
    return true;
}

// Função principal que chama todas as subfunções de verificação
bool syntax_analyzer(const char *input)
{
    return parentheses_checker(input) &&
           quote_checker(input) &&
           invalid_input_checker(input) &&
           redirection_checker(input) &&
           pipe_checker(input) &&
           multiple_operator_checker(input);
}
