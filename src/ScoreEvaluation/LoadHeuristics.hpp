

// #include <map>
// #include "alphabetparameters.h"


// class StrategyParameters
// {
//     public:
//         StrategyParameters();

//         void initialize(const string &lexicon);
//         bool hasSyn2() const;
//         bool hasWorths() const;
//         bool hasVcPlace() const;
//         bool hasBogowin() const;
//         bool hasSuperleaves() const;

//         // letters are raw letters include bottom marks
//         double syn2(Letter letter1, Letter letter2) const;
//         double tileWorth(Letter letter) const;
//         double vcPlace(int start, int length, int consbits);
//         double bogowin(int lead, int unseen, int blanks);
//         double superleave(LetterString leave);

//     protected:
//         bool loadSyn2(const string &filename);
//         bool loadWorths(const string &filename);
//         bool loadVcPlace(const string &filename);
//         bool loadBogowin(const string &filename);
//         bool loadSuperleaves(const string &filename);

//         int mapLetter(Letter letter) const;

//         double m_syn2[QUACKLE_FIRST_LETTER + QUACKLE_MAXIMUM_ALPHABET_SIZE][QUACKLE_FIRST_LETTER + QUACKLE_MAXIMUM_ALPHABET_SIZE];
//         double m_tileWorths[QUACKLE_FIRST_LETTER + QUACKLE_MAXIMUM_ALPHABET_SIZE];
//         double m_vcPlace[QUACKLE_MAXIMUM_BOARD_SIZE][QUACKLE_MAXIMUM_BOARD_SIZE][128];

//         static const int m_bogowinArrayWidth = 601;
//         static const int m_bogowinArrayHeight = 94;
//         double m_bogowin[m_bogowinArrayWidth][m_bogowinArrayHeight];
//         typedef map<LetterString, double> SuperLeavesMap;
//         SuperLeavesMap m_superleaves;
//         bool m_hasSyn2;
//         bool m_hasWorths;
//         bool m_hasVcPlace;
//         bool m_hasBogowin;
//         bool m_hasSuperleaves;
//     };

//     inline bool StrategyParameters::hasSyn2() const
//     {
//         return m_hasSyn2;
//     }

//     inline bool StrategyParameters::hasWorths() const
//     {
//         return m_hasWorths;
//     }

//     inline bool StrategyParameters::hasVcPlace() const
//     {
//         return m_hasVcPlace;
//     }

//     inline bool StrategyParameters::hasBogowin() const
//     {
//         return m_hasBogowin;
//     }

//     inline bool StrategyParameters::hasSuperleaves() const
//     {
//         return m_hasSuperleaves;
//     }

//     inline int StrategyParameters::mapLetter(Letter letter) const
//     {
//         // no mapping needed
//         return letter;
//     }

//     inline double StrategyParameters::syn2(Letter letter1, Letter letter2) const
//     {
//         return m_syn2[mapLetter(letter1)][mapLetter(letter2)];
//     }

//     inline double StrategyParameters::tileWorth(Letter letter) const
//     {
//         return m_tileWorths[mapLetter(letter)];
//     }

//     inline double StrategyParameters::vcPlace(int start, int length, int consbits)
//     {
//         if ((consbits < 0) || (consbits >= 128) ||
//             (start < 0) || (start >= QUACKLE_MAXIMUM_BOARD_SIZE) ||
//             (length < 0) || (length >= QUACKLE_MAXIMUM_BOARD_SIZE))
//             return 0;

//         return m_vcPlace[start][length][consbits];
//     }

//     inline double StrategyParameters::bogowin(int lead, int unseen, int /* blanks */)
//     {
//         if (lead < -300)
//             return 0;
//         if (lead > 300)
//             return 1;

//         if (unseen > 93)
//             unseen = 93;

//         if (unseen == 0)
//         {
//             if (lead < 0)
//                 return 0;
//             else if (lead == 0)
//                 return 0.5;
//             else
//                 return 1;
//         }

//         return m_bogowin[lead + 300][unseen];
//     }

//     inline double StrategyParameters::superleave(LetterString leave)
//     {
//         if (leave.length() == 0)
//             return 0.0;
//         return m_superleaves[leave];
//     }
// }