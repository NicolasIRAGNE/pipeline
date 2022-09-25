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

    ~Node() = default;

    virtual Output process(Input input)
    {
        return m_function(input);
    }
};

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

class Printer : public Node<std::string, std::string>
{
public:
    Printer() = default;

    virtual ~Printer() = default;

    std::string process(std::string input) override
    {
        std::cout << input << std::endl;
        return input;
    }
};

template <typename T>
class PassThrough : public Node<T, T>
{
public:
    PassThrough() = default;

    virtual ~PassThrough() = default;

    T process(T input) override
    {
        return input;
    }
};

template <typename N1, typename N2>
Node<typename N1::InputType, typename N2::OutputType> operator>>(N1& n1, N2& n2)
{
    return Node<typename N1::InputType, typename N2::OutputType>([n1, n2](auto input) mutable
        { return n2.process(n1.process(input)); });
}

template <typename N1, typename N2>
Node<typename N1::InputType, typename N2::OutputType> operator>>(N1&& n1, N2& n2)
{
    return Node<typename N1::InputType, typename N2::OutputType>([n1, n2](auto input) mutable
        { return n2.process(n1.process(input)); });
}

template <typename N1, typename N2>
Node<typename N1::InputType, typename N2::OutputType> operator>>(N1& n1, N2&& n2)
{
    return Node<typename N1::InputType, typename N2::OutputType>([n1, n2](auto input) mutable
        { return n2.process(n1.process(input)); });
}

template <typename N1, typename N2>
Node<typename N1::InputType, typename N2::OutputType> operator>>(N1&& n1, N2&& n2)
{
    return Node<typename N1::InputType, typename N2::OutputType>([n1, n2](auto input) mutable
        { return n2.process(n1.process(input)); });
}

}
