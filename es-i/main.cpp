// #include <iostream>
// #include <vector>

// int main() {
//     size_t rows; // N
//     size_t cols;
//     std::cin >> rows >> cols;

//     std::vector<std::vector<char>> matrix(rows, std::vector<char>(cols));

//     for (size_t i = 0; i < rows; i++) {
//         for (size_t j = 0; j < cols; j++) {
//             std::cin >> matrix.at(i)[j];
//         }
//     }

// ////     std::cout << "Matrix:" << std::endl;

//     for(size_t i = 0; i < rows; i++) {
//         for(size_t j = 0; j < cols; j++) {
// ////             std::cout << matrix.at(i)[j];
//         }
// ////         std::cout << std::endl;
//     }

//     return 0;
// }

// /**
//   P => starting point
//   B => Ending point
//   . => valid path
//   # => invalid path
//   S => Shuttle

//   - => Visited
//  */
// int shortest_path(
//   int current_row,
//   int current_col,
//   std::vector<std::vector<char>>& matrix
// ) {
//   // Invalid row
//   if (current_row < 0 || current_row >= matrix.size()) return -1;

//   // Invalid column
//   if (current_col < 0 || current_col >= matrix.at(current_row).size()) return -1

//   // Found path.
//   if (current_cell == 'B') return 0;

//   // Invalid path.
//   if (current_cell == '#') return -1;

//   char current_cell = matrix.at(current_row)[current_col];
//   matrix.at(current_row)[current_col] = '-';
// }


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

int shortest_path(
  std::vector<std::vector<char>> matrix,
  size_t current_row,
  size_t current_col,
  size_t destination_row,
  size_t destination_col
) {
  if (current_row < 0 || current_row >= matrix.size()) return -1;
  if (current_col < 0 || current_col >= matrix.at(current_row).size()) return -1;

  // Success! Found path.
  if (current_row == destination_row && current_col == destination_col) {
    // //// std::cout << "Found path!" << std::endl;
    return 1;
  }

  if (matrix.at(current_row)[current_col] == '#') return -1;

  // //std::cout << "shortest_path from(" << current_row << ", " << current_col << ")" << " to (" << destination_row << ", " << destination_col << ")" << std::endl;

  int min_possible_distance = std::abs((int)current_row - (int)destination_row) + std::abs((int)current_col - (int)destination_col);

  if (min_possible_distance == 1) {
    // //// std::cout << "min distance 1" << std::endl;
    return 1;
  }

  // char current_cell = matrix.at(current_row)[current_col];
  matrix.at(current_row)[current_col] = '#';

  int up = current_row > 0 ? shortest_path(matrix, current_row - 1, current_col, destination_row, destination_col) : -1;
  if (up + 1 == min_possible_distance) {
    return min_possible_distance;
  }

  int down = shortest_path(matrix, current_row + 1, current_col, destination_row, destination_col);
  if (down + 1 == min_possible_distance) {
    // //std::cout << "down is min distance: " << down << std::endl;
    return min_possible_distance;
  }

  int left = current_col > 0 ? shortest_path(matrix, current_row, current_col - 1, destination_row, destination_col) : -1;
  if (left + 1 == min_possible_distance) {
    // //std::cout << "left is min distance: " << left << std::endl;
    return min_possible_distance;
  }

  int right = shortest_path(matrix, current_row, current_col + 1, destination_row, destination_col);
    // //// std::cout << "right is " << right << " min: " << min_possible_distance << std::endl;
  if (right + 1 == min_possible_distance) {
    // //std::cout << "right is min distance: " << right << std::endl;
    return min_possible_distance;
  }

  // matrix.at(current_row)[current_col] = current_cell;

  if (up == -1 && down == -1 && left == -1 && right == -1) return -1;

  int min_distance = -1;

  if (down != -1 && (min_distance == -1 || down < min_distance)) min_distance = down;
  if (up != -1 && (min_distance == -1 || up < min_distance)) min_distance = up;
  if (left != -1 && (min_distance == -1 || left < min_distance)) min_distance = left;
  if (right != -1 && (min_distance == -1 || right < min_distance)) min_distance = right;

  if (min_distance == -1) {
    std::cerr << "Invalid path" << std::endl;
    exit(1);
  }

/*
  // //std::cout << "returning " << min_distance + 1 << " where " << \
    "up: " << up << ", " << \
    "down: " << down << ", " << \
    "left: " << left << ", " << \
    "right: " << right << std::endl;
    */

  return min_distance + 1;
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

  /**
    Intuizione:
    - Calcolo il tempo minimo andando a piedi
    - Poi calcolo il tempo minimo andando con lo shuttle. In questo caso, dovrò calcolare il tempo per andare verso la fermata dal punto di partenza e sommarla al tempo necessario per andare dalla fermata al punto di arrivo.
   */
   // //std::cout << "Start row: " << start_row << std::endl;
    // //std::cout << "Start col: " << start_col << std::endl;
    // //std::cout << "End row: " << end_row << std::endl;
    // //std::cout << "End col: " << end_col << std::endl;
    int ideal_foot_time = std::abs((int)start_row - (int)end_row) + std::abs((int)start_col - (int)end_col);
    // int distance_to_end = std::abs(start_row - end_row) + std::abs(start_col - end_col);
    // std::vector<int> start_to_shuttles_distances;
    // std::vector<int>
    // std::vector<int> shuttles_distances;
    // int closest_shuttle_x = -1;
    // int closest_shuttle_y = -1;
    // int closest_shuttle_distance = -1;

    // for (size_t i = 0; i < shuttles.size(); i++) {
    //   int ideal_distance = std::abs((int)start_row - (int)shuttles[i].first) + std::abs((int)start_col - (int)shuttles[i].second);
    //   if (ideal_distance > closest_shuttle_distance) {
    //     // We're already too far from the shuttle.
    //     continue;
    //   }

    //   int start_to_shuttle = shortest_path(matrix, start_row, start_col, shuttles[i].first, shuttles[i].second);
    //   if (start_to_shuttle == -1 || closest_shuttle_distance < start_to_shuttle ) continue;

    //   int shuttle_to_end = shortest_path(matrix, shuttles[i].first, shuttles[i].second, end_row, end_col);
    //   if (shuttle_to_end == -1) continue; // useless

    //   shuttles_distances.push_back(start_to_shuttle + shuttle_to_end);
    // }

    // int shuttle_time = -1;
    // for (size_t i = 0; i < shuttles_distances.size(); i++) {
    //     if (shuttle_time == -1 || shuttles_distances[i] < shuttle_time) {
    //         shuttle_time = shuttles_distances[i];
    //     }
    // }

    // pair<size_t, size_t> closest_shuttle = shuttles[0];

    /**
      Shuttle to take
     */

    int shuttle_to_take = -1;
    int shuttle_to_take_distance = -1;

    for(size_t i = 0; i < shuttles.size(); i++) {
      std::pair<size_t, size_t> spos = shuttles[i];
      int ideal_distance = std::abs((int)start_row - (int)spos.first) + std::abs((int)start_col - (int)spos.second);
      if (ideal_distance > shuttle_to_take_distance && shuttle_to_take_distance != -1) {
        // We're already too far from the shuttle.
        // std::cout << "Too far from shuttle" << std::endl;
        continue;
      }

      // if (foot_time < ideal_distance) {
      //   // We're already too far from the shuttle.
      //   // std::cout << "Too far from shuttle; foot will be faster." << std::endl;
      //   continue;
      // }

      std::cout << "calculating start=>shuttle " << spos.first << ", " << spos.second << std::endl;
      int start_to_shuttle = shortest_path(matrix, start_row, start_col, spos.first, spos.second);
      if (start_to_shuttle == -1 || (shuttle_to_take_distance != -1 && shuttle_to_take_distance < start_to_shuttle)) continue;

      shuttle_to_take = i;
      shuttle_to_take_distance = start_to_shuttle;
    }

    if (shuttle_to_take != -1) {
      // std::cout << "i: " << shuttle_to_take << " shuttle_to_take: " << shuttles[shuttle_to_take].first << ", " << shuttles[shuttle_to_take].second <<  " shuttle_to_take_distance: " << shuttle_to_take_distance << std::endl;
    }


    // Shuttle to arrive
    int shuttle_to_arrive = -1;
    int shuttle_to_arrive_distance = -1;

    for(size_t i = 0; i < shuttles.size(); i++) {
      std::pair<size_t, size_t> spos = shuttles[i];
      // int ideal_distance = std::abs((int)end_row - (int)spos.first) + std::abs((int)end_col - (int)spos.second);

      // if (foot_time < ideal_distance) {
      //   // We're already too far from the shuttle.
      //   // std::cout << "Too far from shuttle; foot will be faster." << std::endl;
      //   continue;
      // }

      std::cout << "calculating shuttle=>end " << spos.first << ", " << spos.second << std::endl;
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
      std::cout << "calculating foot time" << std::endl;
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

    // std::cout << "Matrix:" << std::endl;
    for(size_t i = 0; i < rows; i++) {
        for(size_t j = 0; j < cols; j++) {
            // std::cout << matrix.at(i)[j];
        }
        // std::cout << std::endl;
    }

    return 0;
}

// int shortest_path(
//   std::vector<std::vector<char>>& matrix,
//   int current_row,
//   int current_col,
//   int destination_row,
//   int destination_col
// ) {
//   // Invalid row
//   if (current_row < 0 || current_row >= matrix.size()) return -1;

//   // Invalid column
//   if (current_col < 0 || current_col >= matrix.at(current_row).size()) return -1;

//   // Found path.
//   if (current_row == destination_row && current_col == destination_col) return 0;

//   // Invalid path.
//   if (matrix.at(current_row)[current_col] == '#') return -1;

//   char current_cell = matrix.at(current_row)[current_col];
//   matrix.at(current_row)[current_col] = '-';

//   int up = shortest_path(matrix, current_row - 1, current_col, destination_row, destination_col);
//   int down = shortest_path(matrix, current_row + 1, current_col, destination_row, destination_col);
//   int left = shortest_path(matrix, current_row, current_col - 1, destination_row, destination_col);
//   int right = shortest_path(matrix, current_row, current_col + 1, destination_row, destination_col);

//   matrix.at(current_row)[current_col] = current_cell;

//   if (up == -1 && down == -1 && left == -1 && right == -1) return -1;

//   int min_distance = -1;

//   if (up != -1) {
//     min_distance = up;
//   }

//   if (down != -1) {
//     if (min_distance == -1 || down < min_distance) {
//       min_distance = down;
//     }
//   }

//   if (left != -1) {
//     if (min_distance == -1 || left < min_distance) {
//       min_distance = left;
//     }
//   }

//   if (right != -1) {
//     if (min_distance == -1 || right < min_distance) {
//       min_distance = right;
//     }
//   }

//   return min_distance + 1;
// }