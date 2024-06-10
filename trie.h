#ifndef TRIE_H
#define TRIE_H

#include <QObject>

class TrieNode {
public:
    QVector<TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : children(26, nullptr), isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void append(const QString& word) {
        TrieNode* node = root;
        for (QChar ch : word) {
            int index = ch.toLatin1() - 'a';
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }

    QStringList search(const QString& prefix) {
        QStringList ret;
        TrieNode* node = root;
        for (QChar ch : prefix) {
            if (!ch.isLower()) {
                return ret;
            }
            int index = ch.toLatin1() - 'a';
            if (node->children[index] == nullptr) {
                return ret;
            }
            node = node->children[index];
        }
        collectAllWords(node, prefix, ret);
        return ret;
    }


    void clear() {
        clearNode(root);
        root = new TrieNode();
    }

private:
    void clearNode(TrieNode* node) {
        for (int i = 0; i < 26; ++i) {
            if (node->children[i] != nullptr) {
                clearNode(node->children[i]);
                delete node->children[i];
                node->children[i] = nullptr;
            }
        }
    }

    void collectAllWords(TrieNode* node, const QString& prefix, QStringList& ret) {
        if (node->isEndOfWord) {
            ret.append(prefix);
        }
        for (int i = 0; i < 26; ++i) {
            if (node->children[i] != nullptr) {
                QChar ch = 'a' + i;
                collectAllWords(node->children[i], prefix + ch, ret);
            }
        }
    }
};

#endif // TRIE_H
