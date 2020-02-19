#pragma once

#include "TreeNode.h"
#include <stdlib.h>
#include <fstream>

static void toPng(TreeNode* root, string fname = "TreeNode", bool showNullNodes = false) {
    if (!root) { return; }
    string dot = "digraph " + fname + "{\n";
    vector<string> declares;
    vector<string> points;
    queue<TreeNode*> q;
    q.push(root);
    size_t nullIndex = 0;
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        auto name = string("node") + to_string(size_t(p));
        declares.push_back(name + " [label=\"" + to_string(p->val) + "\"];\n");
        if (p->left) {
            q.push(p->left);
            points.push_back(name + " -> " + string("node") + to_string(size_t(p->left)) + "\n");
        } else if (p->right && showNullNodes) {
            auto nullName = string("node") + to_string(nullIndex++);
            declares.push_back(nullName + " [label=\"null\"];\n");
            points.push_back(name + " -> " + nullName + "\n");
        }
        if (p->right) {
            q.push(p->right);
            points.push_back(name + " -> " + string("node") + to_string(size_t(p->right)) + "\n");
        } else if (p->left && showNullNodes) {
            auto nullName = string("node") + to_string(nullIndex++);
            declares.push_back(nullName + " [label=\"null\"];\n");
            points.push_back(name + " -> " + nullName + "\n");
        }
    }
    for (auto d : declares) {
        dot += d;
    }
    dot += "\n";
    for (auto p : points) {
        dot += p;
    }
    dot += "}";
    
    std::ofstream out(fname + ".dot");
    if (out.is_open()) {
        out.write(dot.data(), dot.size());
        out.close();
        string cmd = "dot -Tpng " + fname + ".dot -o" + fname + ".png";
        system(cmd.data());
    }
}