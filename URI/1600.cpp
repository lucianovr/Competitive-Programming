#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i(a); i < (b); i++)

#define all(c) c.begin(), c.end()
#define UNIQUE(c)                                                                                                      \
    { sort(ALL(c); (c).resize( unique(ALL(c))-c.begin() );                                               \
    }
#define pb push_back
#define D(x)                                                                                                           \
    if (1)                                                                                                             \
        cout << __LINE__ << " " << #x " = " << (x) << endl;
#define D2(x, y) cout << #x " = " << x << "  " << #y " = " << y << endl;
#define DVEC(v, n)                                                                                                     \
    {                                                                                                                  \
        cout << #v << "[] ={ ";                                                                                        \
        rep(i, 0, n) cout << v[i] << " ";                                                                              \
        cout << "}\n";                                                                                                 \
    }
#define mp make_pair
#define fst first
#define snd second
#define isONE(mask, bit) ((mask & (1 << bit))) > 0
#define isZERO(mask, bit) ((mask & (1 << bit))) == 0
#define setBIT(mask, bit) (mask | (1 << bit))

typedef pair<int, int> ii;
typedef long long ll;

typedef vector<int> vi;
typedef vector<ii> vii;

const int INF = 0x3f3f3f3f;
const double EPS = 1e-11;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

#define LIVRE -1
#define DESTINO -2
#define PORTA 0
#define INVALIDO -3

int N, M;
int g[30][30];
pair<int, int> dist[25][25][25][25][1 << 5];

inline bool dentro(int x, int y) { return x >= 0 && x < N && y >= 0 && y < M; }

struct state {
    int xg, yg, xb, yb, mask;
    ii d;
    state(){};
    state(int _xg, int _yg, int _xb, int _yb, int _mask, ii _d) {
        xg = _xg;
        yg = _yg;
        xb = _xb;
        yb = _yb;
        mask = _mask;
        d = _d;
    }

    bool operator<(state q) const {
        if (d.fst == q.d.fst)
            return d.snd < q.d.snd;
        return d.fst < q.d.fst;
    }
};

ii soma(ii pa, ii pb) { return ii(pa.fst + pb.fst, pa.snd + pb.snd); }

ii bfs(int xg, int yg, int xb, int yb, int aux) {
    // 	priority_queue<state> PQ;
    queue<state> PQ;
    int mask = 0;
    int a, b;
    ii ans = ii(INF, INF);

    rep(i, 0, N) rep(j, 0, M) rep(k, 0, N) rep(l, 0, M) rep(u, 0, 1 << aux) dist[i][j][k][l][u] = ii(INF, INF);

    PQ.push(state(xg, yg, xb, yb, mask, ii(0, 0)));
    dist[xg][yg][xb][yb][0] = ii(0, 0);

    while (!PQ.empty()) {
        state T = PQ.front();
        PQ.pop();

        xg = T.xg;
        yg = T.yg;
        xb = T.xb;
        yb = T.yb;
        mask = T.mask;
        ii dist_atual = T.d;

        //		printf("\n\nAtual: gato (%d %d), bloco (%d %d), dist (%d %d)\n", xg,yg,xb,yb,T.d.fst, T.d.snd);

        if (dist_atual > dist[xg][yg][xb][yb][mask])
            continue;
        if (g[xb][yb] == DESTINO) {
            ans = min(ans, dist_atual);
        }

        for (int i = 0; i < 4; i++) {
            a = xg + dx[i]; // posicao do gato
            b = yg + dy[i];

            // printf("ngato (%d %d)\n", a, b);
            if (!dentro(a, b)) {
                // printf("fora\n");
                continue;
            }
            if (g[a][b] == INVALIDO) {
                // printf("invalido\n");
                continue;
            }

            if (a != xb || b != yb) // nao vou empurrar o bloco
            {
                // printf("nao empurra\n");
                if (g[a][b] == LIVRE || g[a][b] == DESTINO) { // pode ser livre ou destino
                                                              //	printf("pode\n");
                    if (dist[a][b][xb][yb][mask] > soma(dist_atual, ii(0, 1))) {
                        //		printf("atualiza\n");
                        dist[a][b][xb][yb][mask] = soma(dist_atual, ii(0, 1));
                        PQ.push(state(a, b, xb, yb, mask, dist[a][b][xb][yb][mask]));
                    }
                } else if (g[a][b] >= PORTA) { // pode ser porta

                    int p = g[a][b];     // valor da porta
                    if (isZERO(mask, p)) // porta fechada
                    {
                        //		printf("porta fechada\n");
                        if (dist[a][b][xb][yb][setBIT(mask, p)] > soma(dist_atual, ii(1, 1))) {
                            //			printf("atualiza\n");
                            dist[a][b][xb][yb][setBIT(mask, p)] = soma(dist_atual, ii(1, 1));
                            PQ.push(state(a, b, xb, yb, setBIT(mask, p), dist[a][b][xb][yb][setBIT(mask, p)]));
                        }
                    } else {
                        //		printf("porta aberta\n");
                        if (dist[a][b][xb][yb][mask] > soma(dist_atual, ii(0, 1))) { // porta ja aberta
                                                                                     //			printf("atualiza\n");
                            dist[a][b][xb][yb][mask] = soma(dist_atual, ii(0, 1));
                            PQ.push(state(a, b, xb, yb, mask, dist[a][b][xb][yb][mask]));
                        }
                    }
                }
            }

            else { // estou indo para uma posicao q tem bloco
                // printf("empurrarei o bloco?\n");
                a = xb + dx[i];
                b = yb + dy[i]; // nova posicao do bloco, gato ocupa a posicao antigo do bloco
                // printf("nbloco (%d %d)\n", a, b);

                if (!dentro(a, b)) {
                    // printf("fora\n");
                    continue;
                }
                if (g[a][b] == INVALIDO) {
                    // printf("invalido\n");
                    continue;
                }

                if (g[a][b] == LIVRE || g[a][b] == DESTINO) {
                    // printf("sim\n");
                    if (dist[xb][yb][a][b][mask] > soma(dist_atual, ii(0, 1))) {
                        //	printf("atualiza\n");
                        dist[xb][yb][a][b][mask] = soma(dist_atual, ii(0, 1));
                        PQ.push(state(xb, yb, a, b, mask, dist[xb][yb][a][b][mask]));
                    }
                } else if (g[a][b] >= PORTA) {
                    // printf("tem porta\n");
                    int p = g[a][b];    // o bloco ira ocupar uma porta (ela deve estar aberta)
                    if (isONE(mask, p)) // porta esta aberta?
                    {
                        //	printf("porta aberta\n");
                        if (dist[xb][yb][a][b][mask] > soma(dist_atual, ii(0, 1))) {
                            //		printf("atualiza\n");
                            dist[xb][yb][a][b][mask] = soma(dist_atual, ii(0, 1));
                            PQ.push(state(xb, yb, a, b, mask, dist[xb][yb][a][b][mask]));
                        }
                    }
                    // else printf("porta fechada :(\n");
                }
            }
        }
    }
    return ans;
}

int main() {

    while (scanf("%d %d", &N, &M) == 2) {
        rep(i, 0, N) rep(j, 0, M) g[i][j] = INVALIDO;

        char c;
        int xg, yg, xb, yb, porta = 0;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                scanf(" %c", &c);
                if (c == '*')
                    g[i][j] = INVALIDO;
                else if (c == 'x')
                    g[i][j] = DESTINO;
                else if (c == '.')
                    g[i][j] = LIVRE;
                else if (c == '#')
                    g[i][j] = porta++;
                else if (c == 'j') {
                    g[i][j] = LIVRE;
                    xg = i, yg = j;
                } else if (c == 'b') {
                    g[i][j] = LIVRE;
                    xb = i, yb = j;
                }
            }
        }

        ii ret = bfs(xg, yg, xb, yb, porta);
        if (ret.first == INF || ret.snd == INF)
            printf("-1\n");
        else
            printf("%d %d\n", ret.fst, ret.snd);
    }
    return 0;
}
