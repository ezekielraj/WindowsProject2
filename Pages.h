#include <iostream>
#include <vector>

#ifndef PAGES_H_INCLUDED
#define PAGES_H_INCLUDED

class pages
{
protected:
    std::vector<HWND> pageentries;
public:
    int numofentries = 0;
    virtual void CreatePage() = 0;
    virtual void HandleEvent(WPARAM wParam, LPARAM lParam) = 0;
    virtual void HandleNotifyEvent(WPARAM&, LPARAM&) = 0;
    pages(int n) :pageentries(n)
    {
        numofentries = n;
    }
    void DestroyPage() {
        std::cout << "destroying pages" << std::endl;
        //for (int i = 0; i < numofentries; i++) {
        for (auto it = pageentries.begin(); it != pageentries.end(); ++it) {
            //if (pageentries[i]) {
                DestroyWindow(*it);
            //}
        }
    }
    virtual ~pages() {
        std::cout << "pages destructor" << std::endl;
    }
};



#endif