#ifndef __QUIZBOOK__H__
#define __QUIZBOOK__H__

#include "IQuizBook.h"
#include "UniformRandom.h" // getRandomQuestion
#include "utils.h" // getAllKeys

#include <stdexcept>
#include <functional>

class QuizBook : public IQuizBook 
{
    public:

        QuizBook(){};
        QuizBook(const std::string& str);
        QuizBook(std::istream& is);
         ~QuizBook(){};

        // public event handlers
        std::function<void(const SolvedQuestion&,QuizBook*)> onInsert;
        std::function<void(SolvedQuestion,QuizBook*)> onDelete;
        std::function<void(QuizBook*)> onClear;

        // obtain question
        const SolvedQuestion& getQuestionById(uint32_t id) const;
        const SolvedQuestion& getRandomQuestion(void) const;
        
        // insert a new question
        uint32_t insertQuestion(const SolvedQuestion fQuestion);

        // delete a question
        SolvedQuestion deleteQuestionById(const uint32_t id);

        // check if question exists
        bool hasQuestion(const uint32_t id) const;

        // delete all questions
        void clear(void);

        // save and load
        std::ostream& writeTo(std::ostream& os) const;
        std::istream& readFrom(std::istream& is);

        // stringify the entire quizbook
        std::string serialize() const;

        // number of questions
        size_t size(void) const;

    protected:

        std::map<const uint32_t, const SolvedQuestion> _questions;

        void init(const std::string& str);
        void init(std::stringstream ss);
};

#endif