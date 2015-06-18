#ifndef ELEMENT_H
#define ELEMENT_H

#define MAX_VARIABLES 200

class Element
{
    public:
        Element();
        Element(string netlistLine, )
        ~Element();
        void applyStamp(double Yn[MAX_VARIABLES][MAX_VARIABLES + 1], int numVariables]);
        string getName();
        char getType();
    private:
        string m_Name;
        char m_Type;
        double m_Value;
        int m_A, m_B, m_C, m_D, m_X, m_Y;
        string m_Mode;
};

#endif // ELEMENT_H
