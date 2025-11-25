#ifndef ARO_ARM_CLONEREF_H
#define ARO_ARM_CLONEREF_H

#include <aro/core/arm/RefArray.hpp>

namespace aro {

	template <class T>
	interface Cloneable;

    /**********************************************************************
    *                 Ref<Cloneable<String>> Declaration                  *
    **********************************************************************/

    template <>
    class Ref<Cloneable<String>> : public RefBase
    {
    public:
        Ref();
        virtual ~Ref();
        Ref(const char* chStr);
        Ref(const wchar_t* chStr);
        Ref(Ref<String>&& strRef) noexcept;
        Ref(const Ref<Null>& nRef);
        Ref(const Ref<String>& strRef);
        Ref(Cloneable<String>* strPtr);
        Ref(Ref<Cloneable<String>>&& strRef) noexcept;
        Ref(const Ref<Cloneable<String>>& strRef);

        //dereference operator
        Cloneable<String>* operator->() const;

        //assignment operator
        Ref<Cloneable<String>>& operator=(const char* chStr);
        Ref<Cloneable<String>>& operator=(const wchar_t* chStr);
        Ref<Cloneable<String>>& operator=(Ref<String>&& strRef) noexcept;
        Ref<Cloneable<String>>& operator=(const Ref<Null>& nRef);
        Ref<Cloneable<String>>& operator=(const Ref<String>& strRef);
        Ref<Cloneable<String>>& operator=(Cloneable<String>* strPtr);
        Ref<Cloneable<String>>& operator=(Ref<Cloneable<String>>&& strRef) noexcept;
        Ref<Cloneable<String>>& operator=(const Ref<Cloneable<String>>& strRef);

        //equality/inequality operator
        bool operator==(const Ref<Object>& objRef) const;
        bool operator!=(const Ref<Object>& objRef) const;

    protected:
        Base* ptr() const;
        void clear();

    private:
        Cloneable<String>* ref;

        friend class Ref<Object>;
        template <class T> friend class Ref;
        friend class Weak<Cloneable<String>>;
    };

} /* namespace aro */

#endif /* ARO_ARM_CLONEREF_H */
