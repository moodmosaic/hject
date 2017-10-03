{-# LANGUAGE ForeignFunctionInterface #-}

import System.Environment (getArgs)

foreign import ccall "EjectVolume" ejectVolume :: Char -> IO Bool

main :: IO Bool
main = do
  args <- getArgs
  let vlm = (head . head) args
  ejectVolume vlm
