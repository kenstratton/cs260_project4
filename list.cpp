#include <iostream>
using namespace std;


// Structure of a list element
struct ELMT {
    int id;            // Element Data 1: Location (positive integer)
    int value;         // Element Data 2: Integer value
    struct ELMT *next; // Element Data 3: Pointer indicates an address of a linked element OR NULL
};

static struct ELMT *head = NULL; // A head element in a list
struct ELMT * elmt;              // A element used for searching or deleting a target
struct ELMT * new_elmt;          // A new element
struct ELMT * prev_elmt;         // A element located before a new element


// Check if a list is empty
bool isEmpty() {
    if (head == NULL) {
        return true;
    }
    return false;
}


/*******************************************
 Get fuction :
 * 1. Search a element with a given id (start : head, none -> go to a next element)
 * 2. Return a element OR NULL
********************************************/
struct ELMT * get(int targetId) {
    // * 1
    elmt = head; 
    while (elmt != NULL) {
        if (elmt->id == targetId) {
            break;
        }
        elmt = elmt->next;
    }

    if (elmt != NULL) {
        return elmt; // * 2
    }

    return NULL; // * 2
}


/*******************************************
 Add fuction :
 * 1. Check if a given id is a positive integer
 * 2. Allocate a memory of a list element with id and value
 * 3. Search a position where a new element is inserted (start : head, none -> go to a next element)
 * 4. Position a new element (head OR spot between other two elements)
 * 5. Return bool (success OR failure)
********************************************/
bool add(int id, int value) {
    // * 1
    if (id < 0) {
        return false; // * 5
    }

    // * 2
    new_elmt = (struct ELMT*)malloc(sizeof(struct ELMT));
    new_elmt->id = id;
    new_elmt->value = value;

   // * 3
    elmt = head;
    while (elmt !=  NULL) {
        if (elmt->id > new_elmt->id ) {
            break;
        }
        prev_elmt = elmt;
        elmt = elmt->next;
    }

    // * 4
    if (elmt == head) {
        new_elmt->next = head;
        head = new_elmt;
        return true; // * 5
    } else {
        prev_elmt->next = new_elmt;
        new_elmt->next = elmt;
        return true; // * 5
    }

    return false; // * 5
}


/*******************************************
 Remove fuction :
 * 1. Check emptiness
 * 2. Remove data1 (only a head element in a list)
 * 3. Remove data2 (one from some elements) (start : head, none -> go to a next element)
 * 4. Return a value of a removed element OR 0(a target is not found)
********************************************/
int remove(int targetId) {
    // * 1
    if (isEmpty()) {
        return 0; // * 4
    }

    // * 2
    elmt = head;
    if (elmt->id == targetId) {
        int value = elmt->value;
        head = elmt->next;
        free(elmt);
        return value; // * 4
    }

    // * 3
    while (elmt != NULL) {
        if (elmt->id == targetId) {
            int value = elmt->value;
            prev_elmt->next = elmt->next;
            free(elmt);
            return value; // * 4
        }
        prev_elmt = elmt;
        elmt = elmt->next;
    }

    return 0; // * 4
}


// Check existence of a subject data
void isFound(int targetId) {
    elmt = get(targetId);
    if (elmt == NULL) {
        cout << "Element id:" << targetId << " : Not Found" << endl;
    } else {
        cout << "Element id:" << targetId << " : Found!" << endl;
    }
}


/*******************************************
Test fuction :
 * 1. Test status of emptiness
 * 2. Test add function
 * 3. Test get function
 * 4. Test remove function
********************************************/
void testList() {
    struct ELMT * tmp;
    int removed_data[5];
    int ten = 10;
    int count = 5;
    bool result;

    assert(isEmpty() == true); // * 1

    // * 2
    for (size_t i = 0; i < count; i++) {
        result = add(i, i+ten);
        assert(result == true);
    }
    // * 3
    for (size_t i = 0; i < count; i++) {
        tmp = get(i);
        assert(tmp->id == i);
        assert(tmp->value == i+ten);
    }

    assert(isEmpty() == false); // * 1

    // * 4
    for (size_t i = 0; i < count; i++) {
        removed_data[i] = remove(i);
        assert(removed_data[i] == i+ten);
    }
    // * 3
    for (size_t i = 0; i < count; i++) {
        tmp = get(i);
        assert(tmp == NULL);
    }

    assert(isEmpty() == true); // * 1

    cout << "Tests Done!" << endl;
}


// User Operation
int main() {
    testList();

    int id1 = 1;
    int id2 = 2;

    // Add
    add(id1, 10);
    add(id2, 20);
    isFound(id1);
    isFound(id2);

    // Remove
    remove(id1);
    remove(id2);
    isFound(id1);
    isFound(id2);

    // Must be empty -> no reaction
    remove(id1);
}