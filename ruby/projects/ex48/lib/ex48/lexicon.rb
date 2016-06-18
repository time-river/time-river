#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

module Lexicon

    DIRECTIONS = ["north", "south", "east", "west", "down", "up", "left", "right", "back"]
    VERBS = ["go", "stop", "kill", "eat"]
    STOPS = ["the", "in", "of", "from", "at", "it"]
    NOUNS = ["door", "bear", "princess", "cabinet"]

    def Lexicon.scan(string)
        tokens = string.split(' ')
        pairs = []
        tokens.each do |word|
            if (Lexicon::DIRECTIONS.include?(word))
                pairs.push(["direction", word])
            elsif (Lexicon::VERBS.include?(word))
                pairs.push(["verb", word])
            elsif (Lexicon::STOPS.include?(word))
                pairs.push(["stop", word])
            elsif (Lexicon::NOUNS.include?(word))
                pairs.push(["noun", word])
            elsif (Lexicon.convert_numbers(word))
                pairs.push(["number", Lexicon.convert_numbers(word)])
            else
                pairs.push(["error", word])
            end
        end
        pairs
    end

    def Lexicon.convert_numbers(str)
        begin
            return Integer(str)
        rescue
            return nil
        end
    end

end
