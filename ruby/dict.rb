module Dict
    def Dict.new(num_buckets=256)
        # Initializes a Dict with the given number of buckets.
        aDict = []
        (0...num_buckets).each do |i|
            aDict.push([])
        end
        
        return aDict
    end

    def Dict.hash_key(aDict, key)
        # Given a key this will create a number and then convert it to
        # an index for the aDict's buckets.
        puts "HASH #{key}=#{key.hash}"
        return key.hash % aDict.length
    end

    def Dict.get_bucket(aDict, key)
        # Given a key, find the bucket where it would go.
        bucket_id = Dict.hash_key(aDict, key)
        return aDict[bucket_id]
    end

    def Dict.get_slot(aDict, key, default=nil)
        # Returns the index, key, and value of a slot found in a bucket.
        bucket = Dict.get_bucket(aDict, key)
        
        bucket.each_with_index do |kv, i|
            k, v = kv
            if key == k
                return i, k, v
            end
        end
        
        return -1, key, default
    end

    def Dict.get(aDict, key, default=nil)
        # Gets the value in a bucket for the given key, or the default.
        i, k, v = Dict.get_slot(aDict, key, default=default)
        return v
    end

    def Dict.set(aDict, key, value)
        # Sets the key to the value, replacing any existing value.
        bucket = Dict.get_bucket(aDict, key)
        i, k, v = Dict.get_slot(aDict, key)

        if i >= 0
            bucket[i] = [key, value]
        else
            bucket.push([key, value])
        end
    end

    def Dict.delete(aDict, key)
        # Deletes the given key from the Dict
        bucket = Dict.get_bucket(aDict, key)
        
        (0...bucket.length).each do |i|
            k, v = bucket[i]
            if key == k
                bucket.delete_at(i)
                break
            end
        end
    end

    def Dict.list(aDict)
        # Prints out what's in the Dict
        aDict.each do |bucket|
            if bucket
                bucket.each {|k, v| puts k, v}
            end
        end
    end
end
