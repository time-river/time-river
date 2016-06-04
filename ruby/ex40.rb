#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

class Song

    def initialize(lyrics)
        @lyrics = lyrics
    end

    def sing_me_a_song()
        @lyrics.each {|line| puts line}
    end
end

happy_bday = Song.new(["Happy birthday to you",
                       "I don't want to get sued",
                       "So I'll stop right there"])

bulls_on_parade = Song.new(["They rally around tha family",
                            "With pockets full of shells"])

happy_bday.sing_me_a_song()

bulls_on_parade.sing_me_a_song()

# use @lyrics which is telling Ruby, 
# "I want the tangerine variable that is part of this object." 
# Ruby uses operators like @ and $ to say where a variable is located. 
# When you did $stdin you were saying, "the global stdin," 
# because $ means global. 
# When you do @lyrics you are saying, 
# "the object's lyrics", because @ means "this object."
