#include <iostream>
#include <vector>
#include <cmath>


/**
  P => starting point
  B => Ending point
  . => valid path
  # => invalid path
  S => Shuttle

  - => Visited
 */
// int shortest_path(
//   std::vector<std::vector<char>> matrix,
//   size_t current_row,
//   size_t current_col,
//   size_t destination_row,
//   size_t destination_col
// ){

// }

// int shortest_path(
//   std::vector<std::vector<char>> matrix,
//   size_t current_row,
//   size_t current_col,
//   size_t destination_row,
//   size_t destination_col
// ) {
//   if (current_row < 0 || current_row >= matrix.size()) return -1;
//   if (current_col < 0 || current_col >= matrix.at(current_row).size()) return -1;

//   // Success! Found path.
//   if (current_row == destination_row && current_col == destination_col) {
//     // //// std::cout << "Found path!" << std::endl;
//     return 1;
//   }

//   if (matrix.at(current_row)[current_col] == '#') return -1;

//   // //std::cout << "shortest_path from(" << current_row << ", " << current_col << ")" << " to (" << destination_row << ", " << destination_col << ")" << std::endl;

//   int min_possible_distance = std::abs((int)current_row - (int)destination_row) + std::abs((int)current_col - (int)destination_col);

//   if (min_possible_distance == 1) {
//     // //// std::cout << "min distance 1" << std::endl;
//     return 1;
//   }

//   // char current_cell = matrix.at(current_row)[current_col];
//   matrix.at(current_row)[current_col] = '#';

//   int up = current_row > 0 ? shortest_path(matrix, current_row - 1, current_col, destination_row, destination_col) : -1;
//   if (up + 1 == min_possible_distance) {
//     return min_possible_distance;
//   }

//   int down = shortest_path(matrix, current_row + 1, current_col, destination_row, destination_col);
//   if (down + 1 == min_possible_distance) {
//     // //std::cout << "down is min distance: " << down << std::endl;
//     return min_possible_distance;
//   }

//   int left = current_col > 0 ? shortest_path(matrix, current_row, current_col - 1, destination_row, destination_col) : -1;
//   if (left + 1 == min_possible_distance) {
//     // //std::cout << "left is min distance: " << left << std::endl;
//     return min_possible_distance;
//   }

//   int right = shortest_path(matrix, current_row, current_col + 1, destination_row, destination_col);
//     // //// std::cout << "right is " << right << " min: " << min_possible_distance << std::endl;
//   if (right + 1 == min_possible_distance) {
//     // //std::cout << "right is min distance: " << right << std::endl;
//     return min_possible_distance;
//   }

//   // matrix.at(current_row)[current_col] = current_cell;

//   if (up == -1 && down == -1 && left == -1 && right == -1) return -1;

//   int min_distance = -1;

//   if (down != -1 && (min_distance == -1 || down < min_distance)) min_distance = down;
//   if (up != -1 && (min_distance == -1 || up < min_distance)) min_distance = up;
//   if (left != -1 && (min_distance == -1 || left < min_distance)) min_distance = left;
//   if (right != -1 && (min_distance == -1 || right < min_distance)) min_distance = right;

//   if (min_distance == -1) {
//     std::cerr << "Invalid path" << std::endl;
//     exit(1);
//   }

// /*
//   // //std::cout << "returning " << min_distance + 1 << " where " << \
//     "up: " << up << ", " << \
//     "down: " << down << ", " << \
//     "left: " << left << ", " << \
//     "right: " << right << std::endl;
//     */

//   return min_distance + 1;
// }

// -1 means not visited
// -2 means invalid path
void map_distances(
  std::vector<std::vector<char>> const & board,
  std::vector<std::vector<int>>& result,
  size_t start_row,
  size_t start_col,
  int start_value,
  int coming_from
) {
  // std::cout << "map_distances" << std::endl;
  if (start_row < 0 || start_row >= board.size()) return;
  if (start_col < 0 || start_col >= board.at(0).size()) return;
  if (board[start_row][start_col] == '#') {
    result[start_row][start_col] = -2;
    return;
  }

  // Already visited.
  if (result[start_row][start_col] >= 0 && result[start_row][start_col] < start_value) return;

  result[start_row][start_col] = start_value;

  // Going right on same row
  for(int x0 = 1; x0 < board.at(0).size() - start_col; x0++){
    if (board[start_row][start_col + x0] == '#' || 
        (result[start_row][start_col + x0] >= 0 && result[start_row][start_col + x0] < start_value)) {
      result[start_row][start_col + x0] = -2;
      std::cout << "found wall at " << start_row << ", " << start_col + x0 << std::endl;

      break;
    }

    result[start_row][start_col + x0] = start_value + x0;
  }

  // Going left on same row
  for(int x0 = 0; start_col - x0 > 0; x0++){
    int y = start_col - x0 - 1;
    if (board[start_row][y] == '#' || 
        (result[start_row][y] >= 0 && result[start_row][y] < start_value)) {
      result[start_row][y] = -2;
      break;
    }

    result[start_row][y] = start_value + x0 + 1;
  }

  // Going down on same column
  if (coming_from != 2) map_distances(board, result, start_row + 1, start_col, start_value + 1, 1);

  if (coming_from != 1) map_distances(board, result, start_row - 1, start_col, start_value + 1, 2);
}

std::vector<std::vector<int>> map_distances(
  std::vector<std::vector<char>> const & matrix,
  size_t start_row,
  size_t start_col
) {
  std::vector<std::vector<int>> distances(matrix.size(), std::vector<int>(matrix.at(0).size(), -1));
  map_distances(matrix, distances, start_row, start_col, 0, -1);
  return distances;
}

int shortest_path(
  std::vector<std::vector<char>> const & matrix,
  size_t start_row,
  size_t start_col,
  size_t dest_row,
  size_t dest_col
) {
  // std::vector<std::vector<pair<int, int>>> distances(matrix.size(), std::vector<pair<int, int>>(matrix.at(0).size(), {0, 0}));
  // std::vector<std::vector<pair<int, int>>> distances;
  // Starting from start_row, start_col, will navigate to all directions and save the distance from starting point to an

  std::cout << "shortest_path from (" << start_row << ", " << start_col << ") to (" << dest_row << ", " << dest_col << ")" << std::endl;
  std::vector<std::vector<int>> distances = map_distances(matrix, start_row, start_col);
  std::cout << "Distances from starting point" << std::endl;
  for(size_t i = 0; i < matrix.size(); i++) {
    for(size_t j = 0; j < matrix.at(0).size(); j++) {
      std::cout << distances[i][j] << "\t";
    }
    std::cout << std::endl;
  }

  return 0;
}

int main() {
    size_t rows; // N
    size_t cols;
    std::cin >> rows >> cols;

    std::vector<std::vector<char>> matrix(rows, std::vector<char>(cols));

    size_t start_row = -1;
    size_t start_col = -1;

    size_t end_row = -1;
    size_t end_col = -1;

    std::vector<std::pair<size_t, size_t>> shuttles;

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            std::cin >> matrix.at(i)[j];

            if (matrix.at(i)[j] == 'P') {
                start_row = i;
                start_col = j;
            }

            if (matrix.at(i)[j] == 'B') {
                end_row = i;
                end_col = j;
            }

            if (matrix.at(i)[j] == 'S') {
                shuttles.push_back({i, j});
            }
        }
    }


    std::cout << "Matrix:" << std::endl;
    for(size_t i = 0; i < rows; i++) {
        for(size_t j = 0; j < cols; j++) {
            std::cout << matrix.at(i)[j];
        }
        std::cout << std::endl;
    }

    int just4fun = shortest_path(matrix, start_row, start_col, end_row, end_col);
    std::cout << "Just for fun: " << just4fun << std::endl;

    return 0;

    int ideal_foot_time = std::abs((int)start_row - (int)end_row) + std::abs((int)start_col - (int)end_col);
    /**
      Shuttle to take
     */

    int shuttle_to_take = -1;
    int shuttle_to_take_distance = -1;

    for(size_t i = 0; i < shuttles.size(); i++) {
      std::pair<size_t, size_t> spos = shuttles[i];
      int ideal_distance = std::abs((int)start_row - (int)spos.first) + std::abs((int)start_col - (int)spos.second);
      if (ideal_distance > shuttle_to_take_distance && shuttle_to_take_distance != -1) {
        continue;
      }

      // std::cout << "calculating start=>shuttle " << spos.first << ", " << spos.second << std::endl;
      int start_to_shuttle = shortest_path(matrix, start_row, start_col, spos.first, spos.second);
      if (start_to_shuttle == -1 || (shuttle_to_take_distance != -1 && shuttle_to_take_distance < start_to_shuttle)) continue;

      shuttle_to_take = i;
      shuttle_to_take_distance = start_to_shuttle;
    }


    // Shuttle to arrive
    int shuttle_to_arrive = -1;
    int shuttle_to_arrive_distance = -1;

    for(size_t i = 0; i < shuttles.size(); i++) {
      std::pair<size_t, size_t> spos = shuttles[i];

      // std::cout << "calculating shuttle=>end " << spos.first << ", " << spos.second << std::endl;
      int shuttle_to_and = shortest_path(matrix, spos.first, spos.second, end_row, end_col);
      if (shuttle_to_and == -1 || (shuttle_to_arrive_distance != -1 && shuttle_to_arrive_distance < shuttle_to_and)) continue;

      shuttle_to_arrive = i;
      shuttle_to_arrive_distance = shuttle_to_and;
    }

    if (shuttle_to_arrive != -1) {
      // std::cout << "i: " << shuttle_to_arrive << " shuttle_to_arrive: " << shuttles[shuttle_to_arrive].first << ", " << shuttles[shuttle_to_arrive].second <<  " shuttle_to_arrive_distance: " << shuttle_to_arrive_distance << std::endl;
    }

    int shuttle_time = -1;
    if (shuttle_to_arrive_distance != -1 && shuttle_to_take_distance != -1){
      shuttle_time = shuttle_to_take_distance + shuttle_to_arrive_distance + 1;
    }

      // std::cout << "Shuttle time: " << shuttle_time << std::endl;
    // std::cout << "Foot time: " << foot_time << std::endl;
    int foot_time = -1;
    if (ideal_foot_time < shuttle_time && shuttle_time != -1) {
      // std::cout << "calculating foot time" << std::endl;
      foot_time = shortest_path(matrix, start_row, start_col, end_row, end_col);
    } else {
      std::cout << "dont calc foot time since shuttle is faster" << std::endl;
    }
    // std::cout << ideal_foot_time << std::endl;

    int total = -1;
    if (shuttle_time != -1) total = shuttle_time;
    if (foot_time != -1 && (total == -1 || foot_time < total)) total = foot_time;

    // std::cout << "Min time: " << total << std::endl;
    std::cout << total << std::endl;

    return 0;
}
