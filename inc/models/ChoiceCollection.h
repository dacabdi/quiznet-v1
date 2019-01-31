#ifndef __CHOICECOLLECTION__H__
#define __CHOICECOLLECTION__H__

#include "IChoiceCollection.h"
#include "utils.h" // for map comparison

class ChoiceCollection : public IChoiceCollection
{
    public: 

        ChoiceCollection(const std::string& str);
        ChoiceCollection(std::stringstream& ss);
        ~ChoiceCollection(){};

        // get choices
        const Choice& getChoiceById(const char id) const override;
        const std::map<const char, const Choice>& 
            getAllChoices(void) const override;

        // accounting
        size_t size(void) const override;
        char lastChoiceLetter(void) const override; 

        // stringify
        std::string serialize(void) const override;

        // operators
        bool operator==(const ChoiceCollection& ref) const;
        bool operator!=(const ChoiceCollection& ref) const;
        friend std::ostream& operator<<(
            std::ostream &os, const ChoiceCollection& ref);


    private:

        // data

        std::map<const char, const Choice> _choices;

        // methods

        void init(std::stringstream& ss);

        std::map<const char, const Choice>
            deserializeAllChoices(std::stringstream& ss) const;

        const std::pair<const char, const Choice> 
            deserializeChoice(const std::string& str) const;

        bool validateChoice(const std::string& str) const;
};

#endif // __CHOICECOLLECTION__H__