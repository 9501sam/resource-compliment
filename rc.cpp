#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;

#define NUM_NODE 4
#define NUM_TASK 12

typedef struct {
    int cpu;
    int mem;
    int w;
} node;

typedef struct {
    int cpu;
    int mem;
} task;

node cluster[NUM_NODE];
task tasks[NUM_TASK];

void init_cluster()
{
    cluster[0] = {17, 19};
    cluster[1] = {23, 22};
    cluster[2] = {20, 23};
    cluster[3] = {22, 20};
    for (int i = 0; i < NUM_NODE; i++)
        cluster[i].w = cluster[i].cpu * cluster[i].mem;
};

void init_tasks()
{
    tasks[0] = {8, 6};
    tasks[1] = {7, 3};
    tasks[2] = {7, 10};
    tasks[3] = {6, 3};
    tasks[4] = {6, 5};
    tasks[5] = {6, 6};
    tasks[6] = {5, 5};
    tasks[7] = {5, 7};
    tasks[8] = {4, 3};
    tasks[9] = {2, 4};
    tasks[10] = {2, 6};
    tasks[11] = {1, 3};
};

bool cmp_task(const task &a, const task &b) {
    if (a.cpu != b.cpu)
        return a.cpu > b.cpu;
    return a.mem < b.mem;
}

bool cmp_node(const node &a, const node &b) {
    return a.w > b.w;
}

void resource_complement()
{
    vector<node> _cluster(NUM_NODE);
    vector<task> _tasks(NUM_TASK);
    for (int i = 0; i < NUM_NODE; i++) {
        _cluster[i].cpu = cluster[i].cpu;
        _cluster[i].mem = cluster[i].mem;
    }
    for (int i = 0; i < NUM_TASK; i++) {
        _tasks[i].cpu = tasks[i].cpu;
        _tasks[i].mem = tasks[i].mem;
    }
    sort(_cluster.begin(), _cluster.end(), cmp_node);
    sort(_tasks.begin(), _tasks.end(), cmp_task);
    for (int i = 0; i < NUM_NODE; i++) {
        node *n = &_cluster[i];
        while (!_tasks.empty()) {
            task *t = &_tasks.front();
            if ((n->cpu < t->cpu) || (n->mem < t->mem))
                break;
            n->cpu -= t->cpu;
            n->mem -= t->mem;
            _tasks.erase(_tasks.begin());
        }
        while (!_tasks.empty()) {
            task *t = &_tasks.back();
            if ((n->cpu < t->cpu) || (n->mem < t->mem))
                break;
            n->cpu -= t->cpu;
            n->mem -= t->mem;
            _tasks.pop_back();
        }
    }
    for (int i = 0; i < NUM_NODE; i++) {
        cout << "(" << _cluster[i].cpu << ", " << _cluster[i].mem << ")" << endl;
    }
}

void _resource_complement()
{
    vector<node> _cluster(NUM_NODE);
    vector<task> _tasks(NUM_TASK);
    for (int i = 0; i < NUM_NODE; i++) {
        _cluster[i].cpu = cluster[i].cpu;
        _cluster[i].mem = cluster[i].mem;
        _cluster[i].w = cluster[i].w;
    }
    for (int i = 0; i < NUM_TASK; i++) {
        _tasks[i].cpu = tasks[i].cpu;
        _tasks[i].mem = tasks[i].mem;
    }
    sort(_cluster.begin(), _cluster.end(), cmp_node);
    sort(_tasks.begin(), _tasks.end(), cmp_task);

    for (int i = 0; i < NUM_TASK; i++) {
        task *t = &_tasks[i];
        node *n = &_cluster.front();
        if ((t->cpu > n->cpu) || (t->mem > t->mem))
            continue;
        n->cpu -= t->cpu;
        n->mem -= t->mem;
        n->w = n->cpu * n->mem;
        sort(_cluster.begin(), _cluster.end(), cmp_node);
    }
    
    cout << "---------------" << endl;
    for (int i = 0; i < NUM_NODE; i++) {
        cout << "(" << _cluster[i].cpu << ", " << _cluster[i].mem << ")" << endl;
    }
}

int main()
{
    init_cluster();
    init_tasks();
    resource_complement();
    _resource_complement();
    return 0;
}
