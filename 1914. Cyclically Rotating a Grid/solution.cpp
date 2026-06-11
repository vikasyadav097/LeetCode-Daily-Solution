class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();

        auto extract = [&](int layer) {
            vector<int> elems;
            int top = layer, bot = m - 1 - layer;
            int left = layer, right = n - 1 - layer;

            for (int c = left; c <= right; c++) elems.push_back(grid[top][c]);
            for (int r = top + 1; r <= bot; r++) elems.push_back(grid[r][right]);
            for (int c = right - 1; c >= left; c--) elems.push_back(grid[bot][c]);
            for (int r = bot - 1; r > top; r--) elems.push_back(grid[r][left]);

            return elems;
        };

        auto place = [&](int layer, vector<int>& elems) {
            int top = layer, bot = m - 1 - layer;
            int left = layer, right = n - 1 - layer;
            int i = 0;

            for (int c = left; c <= right; c++) grid[top][c] = elems[i++];
            for (int r = top + 1; r <= bot; r++) grid[r][right] = elems[i++];
            for (int c = right - 1; c >= left; c--) grid[bot][c] = elems[i++];
            for (int r = bot - 1; r > top; r--) grid[r][left] = elems[i++];
        };

        int layers = min(m, n) / 2;
        for (int layer = 0; layer < layers; layer++) {
            auto elems = extract(layer);
            int sz = elems.size();
            int rot = k % sz;
            rotate(elems.begin(), elems.begin() + rot, elems.end());
            place(layer, elems);
        }

        return grid;
    }
};