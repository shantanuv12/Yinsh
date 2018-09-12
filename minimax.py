# Using iterative deepening search for finding better solution is the way to go
# This is the most basic implementation of the minimax algorithm using alpha beta pruning
# This has to be merged with the code of RandomPlayer.py so all the functions are to be studied

def minimax(self):
    v = MaxVal(self)
    return action

def MinVal(self,alpha, beta):
    if(terminal(self)):
        return utility(self)
    for s in children(self):
        child = MaxVal(self,alpha,beta)
        beta = min (beta, child)
        if(alpha>=beta):
            return child
    return best child(min)

def MaxVal(self,alpha, beta):
    if(terminal(self)):
        return utility(self)
    for s in children(self):
        child = MinVal(self,alpha,beta)
        alpha = max (beta, child)
        if(alpha>=beta):
            return child
    return best child(max)
