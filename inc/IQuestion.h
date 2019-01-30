#ifndef __IQUESTION__H__
#define __IQUESTION__H__

#include "Choice.h"

#include <string>
#include <vector>
#include <map>

class IQuestion
{
    public:
        
        virtual uint32_t getId() const = 0;
        virtual std::vector<std::string> getTags() const = 0;
        virtual std::string getQuestion() const = 0;
        virtual std::map<const char, Choice> getAllChoices() const = 0;
        virtual Choice getChoiceById(char id) const = 0;                        
        virtual char getSolution(void) const = 0;
        virtual std::string serialize(void) const = 0;

    protected:

        IQuestion(){};
        ~IQuestion(){};
};

#endif // __IQUESTION__H__