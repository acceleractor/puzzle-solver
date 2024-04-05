# Puzzle Solver

## Usage

To run the puzzle solver, use the following syntax:

compiled_filename -m <path_to_map> -d <start_x> <start_y> <end_x> <end_y>

### Example


puzzle-solver.exe -m ../testMap/map.txt -d 19 127 12 104  

Note: The map files used are all included in the repository.

## TODO 
 - Code Integrity Check: Ensure the maze constitutes a reasonable structure.
 - Customizable Maze Symbols: Enable customization of symbols for walls, obstacles, paths, etc.
 - Customizable Operation Sequence Symbols: Currently, the characters 0123 represent right, left, up, down. This should be customizable.
 - Parameter Completeness Check: Verify that the parameters input by the user are reasonable.  
 
------------------------------------------------------------------------------------------------------------------------------------------------------

## 使用方法
运行迷宫求解器，请使用以下语法：

compiled_filename -m <地图路径> -d <起点x> <起点y> <终点x> <终点y>
### 例如

puzzle-solver.exe -m ../testMap/map.txt -d 19 127 12 104

注意：所使用的地图文件都包含在仓库中。

## TODO
 - 代码完整性检查：确保迷宫构成一个合理的结构。  
 - 自定义迷宫符号：允许自定义墙、障碍物、路径等符号。  
 - 自定义操作序列符号：当前，字符0123代表右、左、上、下。这应该是可以自定义的。  
 - 参数完整性检查：验证用户输入的参数是否合理。  
