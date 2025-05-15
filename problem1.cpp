#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Stack {
private:
    struct Node {
        string url;
        Node* next;
        Node(const string& u, Node* n = nullptr) : url(u), next(n) {}
    };
    Node* topNode;
    int size;

public:
    Stack() : topNode(nullptr), size(0) {}
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(const string& url) {
        Node* newNode = new Node(url, topNode);
        topNode = newNode;
        size++;
    }

    string pop() {
        if (isEmpty()) {
            return "";
        }
        Node* temp = topNode;
        string url = temp->url;
        topNode = topNode->next;
        delete temp;
        size--;
        return url;
    }

    string top() const {
        if (isEmpty()) {
            return "";
        }
        return topNode->url;
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    int getSize() const {
        return size;
    }
};

class BrowserHistory {
private:
    Stack backStack;
    Stack forwardStack;

public:
    void visit(const string& url) {
        forwardStack.clear();
        backStack.push(url);
    }

    string goBack() {
        if (backStack.getSize() <= 1) {
            return "Cannot go back.";
        }
        string current = backStack.pop();
        forwardStack.push(current);
        return backStack.top();
    }

    string goForward() {
        if (forwardStack.isEmpty()) {
            return "Cannot go forward.";
        }
        string url = forwardStack.pop();
        backStack.push(url);
        return url;
    }

    string getCurrentUrl() const {
        return backStack.top();
    }
};

int main() {
    BrowserHistory browser;
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Could not open input file." << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        if (line.substr(0, 5) == "visit") {
            string url = line.substr(5);
            browser.visit(url);
            cout << "Visited: " << url << endl;
        } else if (line == "back") {
            string result = browser.goBack();
            if (result == "Cannot go back.") {
                cout << result << endl;
            } else {
                cout << "Moved back to: " << result << endl;
            }
        } else if (line == "forward") {
            string result = browser.goForward();
            if (result == "Cannot go forward.") {
                cout << result << endl;
            } else {
                cout << "Moved forward to: " << result << endl;
            }
        } else {
            cout << "Invalid command: " << line << endl;
        }
    }

    inputFile.close();
    return 0;
}