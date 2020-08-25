/*
 * Kevin Li
 * kal3552
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way.
 * Please NOTE, you are responsible for ensuring that the functions work correctly in
 * your project solution. Just because the function works correctly in my solution does
 * NOT mean that the function will work correctly in yours.
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that
 * the amount of storage available in the elements[] array is equal to length
 */



/* done for you already */
void destroySet(Set* self) {
    free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
    self->len = 0;
    self->elements = nullptr;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
    self->elements = (int*) malloc(sizeof(int));
    self->elements[0] = x;
    self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
    self->elements = (int*) malloc(other->len * sizeof(int));
    for (int k = 0; k < other->len; k += 1) {
        self->elements[k] = other->elements[k];
    }
    self->len = other->len;
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
    if (self == other) { return; }

    destroySet(self);
    createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
    if(self->len == 0)
    {
        return false;
    }
    int high = self->len - 1;
    int low = 0;
    int mid = high / 2;
    while(high >= low)
    {
        if(self->elements[mid] > x)
        {
            high = mid - 1;
            mid = (low + high) / 2;
        }
        else if(self->elements[mid] < x)
        {
            low = mid + 1;
            mid = (low + high) / 2;
        }
        else if(self->elements[mid] == x)
        {
            return true;
        }
    }
    return false;
}

/*
 * add x as a new member to this set.
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {
    if(self->elements == NULL)
    {
        self->elements = (int*)malloc(sizeof(int));
        self->elements[0] = x;
        self->len++;
        return;
    }
    if(self->elements != NULL && self->len == 0)
    {
        self->elements = (int*)realloc(self->elements, sizeof(int));
        self->elements[0] = x;
        self->len++;
        return;
    }
    if(x > self->elements[self->len - 1])
    {
        self->elements = (int*)realloc(self->elements, (self->len + 1) * sizeof(int));
        self->len++;
        self->elements[self->len-1] = x;
        return;
    }
    uint32_t index = 0;
    while(self->elements[index] <= x)
    {
        if(self->elements[index] == x)
        {
            return;
        }
        index++;
    }
    self->elements = (int*)realloc(self->elements, (self->len + 1) * sizeof(int));
    self->len++;
    for(int i=self->len-1; i>index; i--)
    {
        self->elements[i] = self->elements[i - 1];
    }
    self->elements[index] = x;
    return;
}


/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
    uint32_t index = 0;
    if(self->elements[0] > x || self->len == 0)
    {
        return;
    }
    if(self->elements[self->len - 1] < x)
    {
        return;
    }
    while(1)
    {
        if(self->elements[index] == x)
        {
            break;
        }
        else if(self->elements[index] > x)
        {
            return;
        }
        index++;
    }
    for(int i=index; i<self->len-1; i++)
    {
        self->elements[i] = self->elements[i + 1];
    }
    self->elements[self->len - 1] = 0;
    self->len--;
}

/* done for you already */
void displaySet(const Set* self) {
    int k;

    printf("{");

    if (self->len == 0) {
        printf("}");
    }
    else {
        for (k = 0; k < self->len; k += 1) {
            if (k < self->len - 1) {
                printf("%d,", self->elements[k]);
            } else {
                printf("%d}", self->elements[k]);
            }
        }
    }
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    if(self->len == 0 && other->len == 0)
    {
        return true;
    }
    if(self->len == other->len)
    {
        for(int i=0; i<self->len; i++)
        {
            if(self->elements[i] != other->elements[i])
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
    int otherIndex = other->len - 1;
    int selfIndex = self->len - 1;
    /*for(int i=0; i<self->len; i++)
    {
        bool detector = isMemberSet(other, self->elements[i]);
        if(detector == false)
        {
            return false;
        }
    }
    return true;*/
    if(self->len == 0)
    {
        return true;
    }
    if(other->len == 0)
    {
        return false;
    }
    for(int i=selfIndex; i>=0; i--)
    {
        while((other->elements[otherIndex] > self->elements[i]) && otherIndex > 0)
        {
            otherIndex--;
        }
        if(other->elements[otherIndex] != self->elements[i])
        {
            return false;
        }
    }
    return true;
}

/* done for you */
bool isEmptySet(const Set* self) {
    return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
   /* if(self->len == 0)
    {
        return;
    }
    for(int i=self->len-1; i>=0; i--)
    {
        if(isMemberSet(other, self->elements[i]) == false)
        {
            removeSet(self, self->elements[i]);
        }
    }*/
   if(self->len == 0)
   {
       return;
   }
   int selfIndex = 0;
   int newIndex = 0;
   int newLen = 0;
   int* newElements = (int*)malloc(self->len * sizeof(int));
   for(int i=0; i<other->len; i++)
   {
       while((self->elements[selfIndex] < other->elements[i]) && selfIndex < self->len - 1)
       {
           selfIndex++;
       }
       if(self->elements[selfIndex] == other->elements[i])
       {
           newElements[newIndex] = other->elements[i];
           newLen++;
           newIndex++;
       }
   }
   free(self->elements);
   self->elements = newElements;
   self->len = newLen;
}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
   /* if(self->len == 0 || other->len == 0)
    {
        return;
    }
    for(int i=self->len-1; i>=0; i--)
    {
        if(isMemberSet(other, self->elements[i]) == true)
        {
            removeSet(self, self->elements[i]);
        }
    }*/
    if(self->len == 0 || other->len == 0)
    {
        return;
    }
    int otherIndex = 0;
    int newIndex = 0;
    int newLen = 0;
    int* newElements = (int*)malloc(self->len * sizeof(int));
    for(int i=0; i<self->len; i++)
    {
        while ((other->elements[otherIndex] < self->elements[i]) && (otherIndex < other->len - 1))
        {
            otherIndex++;
        }
        if(self->elements[i] != other->elements[otherIndex])
        {
            newElements[newIndex] = self->elements[i];
            newIndex++;
            newLen++;
        }
    }
    free(self->elements);
    self->elements = newElements;
    self->len = newLen;
}

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
    /* for(int i=0; i<other->len; i++)
    {
        if(isMemberSet(self, other->elements[i]) == false)
        {
            insertSet(self, other->elements[i]);
        }
    }
     */
    if(other->len == 0)
    {
        return;
    }
    if(self->len == 0)
    {
        if(self->elements != nullptr)
        {
            free(self->elements);
        }
        int* copyElements = (int*)malloc(other->len * sizeof(int));
        for(int i=0; i<other->len; i++)
        {
            copyElements[i] = other->elements[i];
        }
        self->len = other->len;
        self->elements = copyElements;
        return;
    }
    int selfIndex = 0;
    int otherIndex = 0;
    int newIndex = 0;
    int newLen = 0;
    int* newElements = (int*)malloc((self->len + other->len) * sizeof(int));
    while(1)
    {
        if(selfIndex == self->len && otherIndex == other->len)
        {
            free(self->elements);
            self->len = newLen;
            self->elements = newElements;
            return;
        }
        else if(selfIndex == self->len)
        {
            newElements[newIndex] = other->elements[otherIndex];
            newLen++;
            otherIndex++;
            newIndex++;
        }
        else if(otherIndex == other->len)
        {
            newElements[newIndex] = self->elements[selfIndex];
            newLen++;
            selfIndex++;
            newIndex++;
        }
        else if(self->elements[selfIndex] > other->elements[otherIndex] && otherIndex < other->len)
        {
            newElements[newIndex] = other->elements[otherIndex];
            newLen++;
            otherIndex++;
            newIndex++;
        }
        else if(self->elements[selfIndex] < other->elements[otherIndex] && selfIndex < self->len)
        {
            newElements[newIndex] = self->elements[selfIndex];
            newLen++;
            selfIndex++;
            newIndex++;
        }
        else if(self->elements[selfIndex] == other->elements[otherIndex])
        {
            newElements[newIndex] = self->elements[selfIndex];
            newLen++;
            selfIndex++;
            otherIndex++;
            newIndex++;
        }
    }
}
