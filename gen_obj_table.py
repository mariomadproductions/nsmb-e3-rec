#!/usr/bin/env python3

import sys
import os.path

inputFilePath = "source/ObjectTable.cpp"
objectFilePath = "build/source/ObjectTable.cpp.o"
outputFilePath = "source/ObjectTable.gen.cpp"

def is_uptodate():
    if not os.path.exists(objectFilePath):
        return False
    return os.path.getmtime(objectFilePath) > os.path.getmtime(inputFilePath)

def get_args(argsLiteral):
    args = argsLiteral.split(',')
    for i in range(0, len(args)):
        args[i] = args[i].strip()
    return args

def main():
    if not os.path.exists(inputFilePath):
        print(f'Error, input file "{inputFilePath}" does not exist.')
        sys.exit(1)

    if is_uptodate():
        sys.exit(0)

    inputFile = open(inputFilePath, "r")
    inputLines = inputFile.readlines()
    
    outputLines = []
    lineNum = 1
    for inputLine in inputLines:
    
        if inputLine.startswith("#include"):
        
            outputLines.append(inputLine)
            
        elif inputLine.startswith("repl_obj("):
        
            endIdx = inputLine.find(')', 9)
            if endIdx == -1:
                print(f"Error, line {lineNum} incomplete!")
                sys.exit(1)
                
            args = get_args(inputLine[9:endIdx])
            argCount = len(args)
            if (argCount != 2):
                print(f"Error on line {lineNum}, expected 2 arguments for repl_obj, got {argCount} instead.")
                sys.exit(1)
                
            objID = int(args[0])
            if objID > 384:
                print(f"Error on line {lineNum}, max value for objID is 384.")
                sys.exit(1)
            objClass = args[1]
            
            profileAddr = hex(0x0203997C + (objID * 4))
            
            outputLines.append(f"ncp_over({profileAddr}) static ObjectProfile* obj{objID}_profile = &{objClass}::profile;\n")
            
        elif inputLine.startswith("repl_stageObj("):
        
            endIdx = inputLine.find(')', 14)
            if endIdx == -1:
                print(f"Error, line {lineNum} incomplete!")
                sys.exit(1)
                
            args = get_args(inputLine[14:endIdx])
            argCount = len(args)
            if (argCount != 3):
                print(f"Error on line {lineNum}, expected 3 arguments for repl_stageObj, got {argCount} instead.")
                sys.exit(1)
                
            objID = int(args[0])
            if objID > 384:
                print(f"Error on line {lineNum}, max value for objID is 384.")
                sys.exit(1)
                
            stageObjID = int(args[1])
            if stageObjID > 325:
                print(f"Error on line {lineNum}, max value for stageObjID is 325.")
                sys.exit(1)
            objClass = args[2]
            
            profileAddr = hex(0x0203997C + (objID * 4))
            objIDAddr = hex(0x020C22B8 + (stageObjID * 2))
            objInfoAddr = hex(0x020C529C + (stageObjID * 20))
            objBankAddr = hex(0x020C5010 + (stageObjID * 2))
            
            outputLines.append(f"ncp_over({profileAddr}) static ActorProfile* obj{objID}_profile = &{objClass}::profile;\n")
            outputLines.append(f"ncp_over({objIDAddr}, 0) const u16 stageObj{stageObjID}_objID = {objID};\n")
            outputLines.append(f"ncp_over({objInfoAddr}, 0) const ObjectInfo stageObj{stageObjID}_info = {objClass}::objectInfo;\n")
            outputLines.append(f"ncp_over({objBankAddr}, 0) const u16 stageObj{stageObjID}_bank = 0;\n")
            
        lineNum += 1
    
    outputFile = open(outputFilePath, "w")
    outputFile.writelines(outputLines)
    sys.exit(0)

if __name__ == "__main__":
    main()
