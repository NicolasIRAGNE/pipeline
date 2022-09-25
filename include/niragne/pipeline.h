/**
 * @file pipeline.h
 * @author Nicolas IRAGNE (nicolas.iragne@alyce.fr)
 * @brief Provides a pipeline class to manage the different steps of a process.
 * A pipeline is a list of successive nodes that take an input and produce an output.
 * @date 2022-09-25
 *
 * @copyright Copyright Alyce (c) 2022
 */

#pragma once

#include <any>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

/**
 # Pipelines dpy



Uniformiser les types de processus, en utilisant la meme structure de pipeline:



On considère 3 types de processus:

- player: juste relire la video et eventuellement les données

- process: lire la video et appliquer le deep learning dessus

- demo: les deux en meme temps, plus ou moins



Si on considere nos nodes de pipeline comme Node<Input, Output>, on peut eventuellement avoir quelque chose comme:



Dans le cas du simple player, on va entrer en input un temps T et on veut en sortie une Frame F qui contient nos objets qui sont chargés via des fichiers deja presents



On peut imaginer les nodes suivants:

- Generator: Node<T, F>

- Loader: Node<F, F>



Maintenant on veut faire de la prod. On a, pareil, un temps T en input, mais en sortie on veut une PFrame pour mettre dans le buffer

on peut imaginer une pipeline un peu comme

- Generator: Node<T, F>

- Detector: Node<F, PF>

- Analyzer: Node<PF, PF>

- Exporter: Node<PF, PF>



En fait ce que je veux dire c'est qu'on pourrait faire des process compatibles meme si ils veulent un output different, parce que les nodes sont capables de changer le type de donnee

EN gardant a l'esprit que l'objet est move entre chaque node, donc pas de copie

 */

namespace niragne
{

template <typename Input, typename Output>
class Node
{

public:
    using ProcessFunction = std::function<Output(Input)>;

private:
    ProcessFunction m_function;

public:
    using InputType = Input;
    using OutputType = Output;

    Node() = default;
    Node(const ProcessFunction& process)
        : m_function(process)
    {
    }

    virtual Output process(Input input)
    {
        return m_function(input);
    }
};

template <typename N1, typename N2>
Node<typename N1::InputType, typename N2::OutputType> operator>>(const N1& n1, const N2& n2)
{
    return Node<typename N1::InputType, typename N2::OutputType>([&n1, &n2](auto input) {
        return n2.process(n1.process(input));
    });
}


class Incrementer : public Node<int, int>
{
public:
    Incrementer(int increment)
        : m_increment(increment)
    {
    }

    virtual ~Incrementer() = default;

    int process(int input) override
    {
        return input + m_increment;
    }

private:
    int m_increment;
};

class Stringifier : public Node<int, std::string>
{
public:
    Stringifier() = default;

    virtual ~Stringifier() = default;

    std::string process(int input) override
    {
        return std::to_string(input);
    }
};

class Printer : public Node<std::string, void>
{
public:
    Printer() = default;

    virtual ~Printer() = default;

    void process(std::string input) override
    {
        std::cout << input << std::endl;
    }
};

}
