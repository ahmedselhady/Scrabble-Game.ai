#include "LoadHeuristics.hpp"

LoadHeuristics::LoadHeuristics()
{
    //Nothing
}

bool LoadHeuristics::loadSyn2(const string &filename)
{
    for (int indexRow = 0; indexRow <= NUM_LETTERS; ++indexRow)
    {
        for (int indexCol = 0; indexCol <= NUM_LETTERS; ++indexCol)
        {
            m_syn2[indexRow][indexCol] = 0;
        }
    }

    std::ifstream syn2File(filename);

    if (!syn2File.is_open())
    {
        cout << "Could not open " << filename << " to load syn2" << endl;
        return false;
    }

    std::string twoLetters = " ";
    while (!syn2File.eof())
    {
        syn2File >> twoLetters;
        if (twoLetters.empty())
        {
            continue;
        }

        if (syn2File.eof())
        {
            break;
        }
        double value;
        syn2File >> value;

        m_syn2[twoLetters[0] - 'A'][twoLetters[1] - 'A'] = value;
        m_syn2[twoLetters[1] - 'A'][twoLetters[0] - 'A'] = value;
    }

    syn2File.close();
    return true;
}

// bool LoadHeuristics::loadBogowin(const string &filename)
// {
//     for (int i = 0; i < m_bogowinArrayWidth; ++i)
//         for (int j = 0; j < m_bogowinArrayHeight; ++j)
//             m_bogowin[i][j] = 0;

//     UVIFStream file(filename.c_str());

//     if (!file.is_open())
//     {
//         cerr << "Could not open " << filename << " to load bogowin heuristic" << endl;
//         return false;
//     }

//     while (!file.eof())
//     {
//         int lead, unseen;
//         double wins;

//         file >> lead;
//         file >> unseen;
//         file >> wins;

//         m_bogowin[lead + 300][unseen] = wins;
//     }

//     file.close();
//     return true;
// }
bool LoadHeuristics::loadWorths(const string &filename)
{
    for (int index = 0; index <= NUM_LETTERS; ++index)
    {
        m_tileWorths[index] = 0;
    }

    std::ifstream worthsFile(filename);

    if (!worthsFile.is_open())
    {
        cerr << "Could not open " << filename << " to load worths" << endl;
        return false;
    }

    char letter = ' ';
    while (!worthsFile.eof())
    {
        worthsFile >> letter;
        // if (letter.empty())
        // {
        //     continue;
        // }

        if (worthsFile.eof())
        {
            break;
        }
        double value;
        worthsFile >> value;

        m_tileWorths[letter - 'A'] = value;
    }

    worthsFile.close();
    return true;
}

bool LoadHeuristics::loadVcPlace(const string &filename)
{
    for (int indexRow = 0; indexRow <= MAX_VC_EMPTY_BOARD_MOVE; ++indexRow)
    {
        for (int indexCol = 0; indexCol <= MAX_VC_EMPTY_BOARD_MOVE; ++indexCol)
        {
            for (int bits = 0; bits < VC_PACKET; ++bits)
            {
                m_vcPlace[indexRow][indexCol][bits] = 0; // init.
            }
        }
    }

    std::ifstream vcFile(filename);

    if (!vcFile.is_open())
    {
        cout << "Could not open " << filename << " to load vcPlace heuristic" << endl;
        return false;
    }

    while (!vcFile.eof())
    {
        unsigned int start;
        vcFile >> start;

        if (vcFile.eof())
        {
            break;
        }

        unsigned int length;
        vcFile >> length;

        if (vcFile.eof())
        {
            break;
        }

        unsigned int consbits;
        vcFile >> consbits;

        if (vcFile.eof())
        {
            break;
        }

        double value;
        vcFile >> value;

        // if ((start < QUACKLE_MAXIMUM_BOARD_SIZE) &&
        //     (length < QUACKLE_MAXIMUM_BOARD_SIZE) &&
        //     (consbits < 128))

        m_vcPlace[start][length][consbits] = value;
    }

    vcFile.close();
    return true;
}

bool LoadHeuristics::loadSuperleaves(const string &filename)
{
    superLeaves.clear();

    ifstream superleaveFile(filename.c_str(), ios::in | ios::binary);

    if (!superleaveFile.is_open())
    {
        cout << "Could not open " << filename << " to load superleave heuristic" << endl;
        return false;
    }

    unsigned char leavesize;
    char leavebytes[16];
    unsigned char intvalueint;
    unsigned char intvaluefrac;
    unsigned int intvalue;

    while (!superleaveFile.eof())
    {
        superleaveFile.read((char *)(&leavesize), 1);
        superleaveFile.read(leavebytes, leavesize);
        superleaveFile.read((char *)(&intvaluefrac), 1);
        superleaveFile.read((char *)(&intvalueint), 1);
        if (superleaveFile.eof())
        {
            break;
        }

        intvalue = (unsigned int)(intvalueint)*256 + (unsigned int)(intvaluefrac);
        vector<char> Rack; //LetterString(leavebytes, leavesize);
        //copy into rack ....

        double value = (double(intvalue) / 256.0) - 128.0;
        superLeaves.insert(superLeaves.end(),
                           SuperLeavesMap::value_type(Rack, value));
    }

    superleaveFile.close();
    return true;
}

double LoadHeuristics::syn2(char letter1, char letter2)
{
    return m_syn2[mapLetter(letter1)][mapLetter(letter2)];
}

double LoadHeuristics::tileWorth(char letter)
{
    return m_tileWorths[mapLetter(letter)];
}

double LoadHeuristics::vcPlace(int start, int length, int consbits)
{
    if ((consbits < 0) || (consbits >= 128) ||
        (start < 0) || (start >= MAX_VC_EMPTY_BOARD_MOVE) ||
        (length < 0) || (length >= MAX_VC_EMPTY_BOARD_MOVE))
    {
        return 0;
    }

    return m_vcPlace[start][length][consbits];
}

// double LoadHeuristics::bogowin(int lead, int unseen, int /* blanks */)
// {
//     if (lead < -300)
//         return 0;
//     if (lead > 300)
//         return 1;

//     if (unseen > 93)
//         unseen = 93;

//     if (unseen == 0)
//     {
//         if (lead < 0)
//             return 0;
//         else if (lead == 0)
//             return 0.5;
//         else
//             return 1;
//     }

//     return m_bogowin[lead + 300][unseen];
// }

double LoadHeuristics::superleave(std::vector<char> *Rack)
{
    if (Rack->size() == 0)
    {
        return 0.0;
    }
    return superLeaves[*Rack];
}