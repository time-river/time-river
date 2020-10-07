#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

class Parent

    def implicit()
        puts "PARENT implicit()"
    end
end

class Child <Parent
end

dad = Parent.new()
son = Child.new()

dad.implicit()
son.implicit()
