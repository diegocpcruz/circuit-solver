#ifndef ELEMENT_H
#define ELEMENT_H

#define MAX_VARIABLES 200

class Element
{
    public:
        int m_X, m_Y;

        Element(string netlistLine)
        void applyStamp(double Yn[MAX_VARIABLES][MAX_VARIABLES + 1], int numVariables]);
        void addCurrentVariables(int& numVariables, vector<Element>& variables);
        string getName();
        char getType();
    private:
        string m_Name;
        char m_Type;
        double m_Value;
        int m_A, m_B, m_C, m_D;
        string m_Mode;
};

#endif // ELEMENT_H
