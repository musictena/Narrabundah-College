# This Sudoku game was created by Phebe Le in Session 2 2023

# Whilst this game may not be able to function in the correct method that a normal sudoku game does

# It is able to use the brute force algorithm to validate if the board is correct or not

# Is randomly generated based on the board (GUI)

# Here random generation works perfectly in terminal (once the GUI solve button is pressed) not in GUI though as it randomly generates based on 3x3 squares


#import libraries and modules

from random import randint

import tkinter as tk



# Define level class

class Level:

  def __init__(self, literal, hints):

    self.literal = literal

    self.hints = hints



# Checking all cells must be fill

def isFullFill(grid):

    for row in range(9):

        for  col in range(9):

            if (grid[row][col] == 0):

                return False

            

    return True





# Checking to see is is a number in row or column

def isValid(grid, row, col, number):

    # check numner in the row

    for x in range(9):

        if grid[row][x] == number:

            return False



    # check number in the column

    for x in range(9):

        if grid[x][col] == number:

            return False



    # check number in the 3x3 square

    corner_row = row - row % 3

    corner_col = col - col % 3

    for x in range(3):

        for y in range (3):

            if grid[corner_row + x][corner_col + y] == number:

                return False

    return True



#

def solve(grid, row, col):

    if col == 9:

        if row == 8:

            return True

        row += 1

        col = 0



    if grid[row][col] > 0:

        return solve(grid, row, col + 1)



    for num in range (1,10):

        if isValid(grid, row, col, num):

            grid[row][col] = num

            if solve(grid, row, col+1):

                return True

        grid[row][col] = 0

    return False





def load_board(level: Level):

    main.tkraise() # set menu frame in front of other windows

    cells={}

    color="#D0ffff"

    board = tk.Tk()



    label=tk.Label(board, text="Solve by filling in the numbers", font=("times", 15, 'bold')).grid(row=0, column=0, columnspan=10)

    # label to tell user about correct board (in regards to design)

    solvedLabel=tk.Label(board, text="", fg="green")

    solvedLabel.grid(row=14, column=1, columnspan=10, pady=5)



    # label to tell user about incorrect board (in regards to design)

    errorLabel=tk.Label(board, text="", fg="red")

    errorLabel.grid(row=14, column=1, columnspan=10, pady=5)



    # generate title based on chosen button

    board.title("Sudoku Board - " + level.literal)

    board.geometry("350x440")

    board.resizable(width=False, height=False)



    # validation of the input text

    def ValidateNumber(P):

        out=(P.isdigit() or P=="") and len(P)<2 #validation of the number

        return out



    # have board register this validation method

    reg = board.register(ValidateNumber)



    # to clear all numbers within the board (for button)

    def clearValues():

        errorLabel.configure(text="")

        solvedLabel.configure(text="")

        for row in range(2,11):

            for col in range(1,10):

                cell = cells[(row,col)]

                cell.delete(0,"end")



    # method to solve the board, this does not work in the gui but if real data is inputted, it uses backtracting to solve

    def solved():

        board = []

        solvedLabel.configure(text="")

        errorLabel.configure(text="")

        for row in range(2,11):

            rows=[]

            for col in range(1,10):

                val = cells[(row,col)].get()

                if val == "":

                    rows.append(0)

                else:

                    rows.append(int(val))

            board.append(rows)



        # remove any duplicate number in the same row

        newBoard=[]

        for i in range(0,9):

            row1=board[i]

            new_row = []

            for one in row1:

                if one > 0 and one in new_row:

                    new_row.append(0)

                else:

                    new_row.append(one)

            newBoard.append(new_row)



        # print the new board into the terminal

        for i in range(9):

           print(newBoard[i])

        print()



        # Check all cells must fill

        if isFullFill(newBoard):

            if solve(newBoard, 0, 0):

                solvedLabel.configure(text="The puzzle has been solved")

            else:

                errorLabel.configure(text="Incorrect or invalid answer")

        else:

            errorLabel.configure(text="Require to fill all cells")



    # draw the board with the entry and random generation

    def draw3x3Grid(row,column, bgcolor):

        randomList=[]

        for i in range(3):

            for j in range(3):

                e= tk.Entry(board, width=5, bg=bgcolor, justify="center", validate="key", validatecommand=(reg, "%P"))

                aNum=randint(0, 9)

                if len(randomList) < level.hints:

                    if aNum not in randomList:

                        randomList.append(aNum)

                        if aNum == 0:

                            aNum = ""

                        e.insert(0, aNum)

                e.grid(row=row+i+1, column=column+j+1,sticky="nsew", padx=1, pady=1, ipady=5)

                cells[(row+i+1,column+j+1)]=e



    # creating the board 9x9 that can input numbers

    for rowNo in range(1,10,3):

        for colNo in range(0,9,3):

            draw3x3Grid(rowNo, colNo, color)

            if color == "#D0ffff":

                color = "light blue"

            else:

                color = "#D0ffff"



    # button to quit the window



    CloseBttn = tk.Button(board,

                    text='Quit',

                    command=lambda:board.destroy())



    # button to solve puzzle and validate it

    solveBttn = tk.Button(board,

                    text='Solve',

                    width=5,

                    fg='black',

                    bg='white',

                    cursor="hand2",

                    activebackground="#badee2",

                    activeforeground="black",

                    command=lambda:solved())



    # button to clear puzzle

    ClearBttn = tk.Button(board,

                    text='Clear',

                    command=lambda:clearValues())



    # design aspect of the buttons

    CloseBttn.grid(row=15, column=2, pady=5)

    solveBttn.grid(row=15, column=4, pady=5)

    ClearBttn.grid(row=15, column=6, pady=5)



def load_main():

    # working this is used to check the validation and bruteforce method of the code

    sample = [[9, 5, 7, 6, 1, 3, 2, 8, 4],

              [4, 8, 3, 2, 5, 7, 1, 9, 6],

              [6, 1, 2, 8, 4, 9, 5, 3, 7],

              [1, 7, 8, 6, 3, 4, 9, 5, 2],

              [5, 2, 4, 9, 7, 1, 3, 6, 8],

              [3, 6, 9, 5, 2, 9, 7, 4, 1],

              [8, 4, 5, 7, 9, 2, 6, 1, 3],

              [2, 9, 1, 4, 3, 6, 8, 7, 5],

              [7, 3, 6, 1, 8, 5, 4, 2, 9]]



    # set up levels

    easyLevel = Level("Easy", 5)

    mediumLevel = Level("Medium", 4)

    hardLevel = Level("Hard", 3)



    # print board in terminal

    for i in range(9):

        print(sample[i])



    # check using bruteforce

    if solve(sample, 0, 0):

        print("The sample puzzle is working")

    else:

        print("The sample puzzle is NOT valid")



    # place in front of other windows

    board.tkraise()

    main.pack_propagate(False)



    # Step 1.2. Create the menu buttons and the diversion to external window

    title = tk.Label(main, text="SUDOKU", bg="light blue", font=("times", 40, 'bold'))

    subheading= tk.Label(main, bg="light blue", text="Select a difficulty to play")



    easyBttn = tk.Button(main,

                    text=easyLevel.literal,

                    width = 40,

                    height=10,

                    fg='black',

                    bg='white',

                    cursor="hand2",

                    activebackground="#badee2",

                    activeforeground="black",

                    command=lambda:load_board(easyLevel))



    mediumBttn = tk.Button(main,

                    text=mediumLevel.literal,

                    width = 40,

                    height=10,

                    fg='black',

                    bg='white',

                    cursor="hand2",

                    activebackground="#badee2",

                    activeforeground="black",

                    command=lambda:load_board(mediumLevel))



    hardBttn = tk.Button(main,

                    text=hardLevel.literal,

                    width = 40,

                    height=10,

                    fg='black',

                    bg='white',

                    cursor="hand2",

                    activebackground="#badee2",

                    activeforeground="black",

                    command=lambda:load_board(hardLevel))



    title.grid(row = 3, column = 1, padx=30, pady=10)

    subheading.grid(row = 4, column = 1, padx=30, pady=10)

    easyBttn.grid(row = 3, column = 2, padx=40, pady=10)

    mediumBttn.grid(row = 4, column = 2, padx=40, pady=10)

    hardBttn.grid(row = 6, column = 2, padx=40, pady=10)



# Step 1.1. Set up the main design of the window



root = tk.Tk()

root.title("Sudoku Game")

root.geometry("650x540")

root.resizable(width=False, height=False)

root.configure(bg="light blue")

root.grid_rowconfigure(1, weight=1)

root.grid_columnconfigure(1, weight=1)

main = tk.Frame(root, width=850, height=540, bg="light blue")

board = tk.Frame(root, bg="black")

main.grid(row=0, column=0)

board.grid(row=0, column=0)



# Main

load_main()



root.mainloop()
