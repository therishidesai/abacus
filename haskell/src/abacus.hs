module Main (main) where

import System.IO

import Text.ParserCombinators.Parsec
import Text.ParserCombinators.Parsec.Expr

data CalcExpr  = Num Double
               | Neg CalcExpr
               | Add  CalcExpr CalcExpr
               | Sub CalcExpr CalcExpr
               | Mul CalcExpr CalcExpr
               | Div CalcExpr CalcExpr

number :: GenParser Char st CalcExpr
number = do
  x <- many1 digit
  let x' = (read x :: Double)
  return (Num x')

parseNeg :: GenParser Char st CalcExpr
parseNeg = do
  o <- oneOf("-")
  f <- parseFact
  return (Neg f)

parseSum :: GenParser Char st (CalcExpr -> CalcExpr -> CalcExpr)
parseSum = do
  o <- oneOf "+-"
  return $ case o of
    '+' -> Add
    '-' -> Sub

parseProd :: GenParser Char st (CalcExpr -> CalcExpr -> CalcExpr)
parseProd = do
  o <- oneOf "*/"
  return $ case o of
    '*' -> Mul
    '/' -> Div

parseTerm :: GenParser Char st CalcExpr
parseTerm = do
  x <- chainl1 parseFact parseProd
  return x

parseFact :: GenParser Char st CalcExpr
parseFact = try parseNeg <|> number <|> between (char '(') (char ')') parseExpr

parseExpr :: GenParser Char st CalcExpr
parseExpr = do
  x <- chainl1 parseTerm parseSum
  return x

eval :: CalcExpr -> Double
eval (Num x) = x
eval (Neg x) = - eval x
eval (Add x y) = (eval x) + (eval y)
eval (Sub x y) = (eval x) - (eval y)
eval (Mul x y) = (eval x) * (eval y)
eval (Div x y) = (eval x) / (eval y)

calculate :: String -> Either ParseError Double
calculate ss = case parse parseExpr "Error" ss of
                     (Left err) -> Left(err)
                     (Right expr) -> Right(eval expr)

calcLoop :: IO ()
calcLoop = do
  putStr "=> "
  hFlush stdout
  i <- getLine
  case calculate i of
    (Left err) -> putStrLn $ "Bad Input: " ++ show err
    (Right val) -> putStrLn $ show val
  calcLoop

main = do
  putStrLn "Abacus!"
  calcLoop
