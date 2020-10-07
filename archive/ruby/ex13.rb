#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

first, second, third = ARGV

puts "Your first variable is: #{first}"
puts "Your second variable is: #{second}"
puts "Your third variable is: #{third}"


puts gets.chomp # 无法与 ARGV 同时存在 

#  can't combine ARGV with gets.chomp.
#  Don't overthink it. Just slap two lines 
#  at the end of this script that uses 
#  gets.chomp to get something and then print it.
#  From that start playing with more ways to 
#  use both in the same script.
