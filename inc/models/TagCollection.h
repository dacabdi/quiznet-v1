#ifndef __TAGCOLLECTION__H__
#define __TAGCOLLECTION__H__

#include "ITagCollection.h"
#include "Tag.h"
#include "utils.h"
#include <vector>
#include <sstream>

class TagCollection : public ITagCollection
{
    public: 

        TagCollection(const std::string& str);
        TagCollection(std::stringstream& ss);

        // get tags
        const Tag& at(const size_t idx) const override;
        const std::vector<Tag>& getAllTags(void) const override;
        
        // accounting
        size_t size(void) const override;

        // stringify
        std::string serialize(void) const override;

        // operators
        bool operator==(const TagCollection& ref) const;
        bool operator!=(const TagCollection& ref) const;
        friend std::ostream& operator<<(
            std::ostream &os, const TagCollection& ref);
        //const Tag& operator[](const size_t idx) const;

    protected:

        std::vector<Tag> _tags;

        std::vector<Tag> deserialize(const std::string& str);
};

#endif // __ITAGCOLLECTION__H__