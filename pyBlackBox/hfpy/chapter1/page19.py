
movies = ["The Holy Grail", 1975, "Terry Jones & Terry Gilliam", 91, 
                ["Graham Chapman", ["Michael Palin", "John Cleese",
                        "Terry Gilliam", "Eric Idle", "Terry Jones"]]]

print(movies)

for each_item in movies:
    print(each_item)
    
for item in movies:
    if isinstance(item, list):
        for each_item in item:
                if isinstance(each_item, list):
                    for eachi_item in each_item:
                        print(eachi_item)
                else:
                    print(each_item)
    else:
        print(item)
        
        
def print_lol(the_list):
    for each_item in the_list:
            if isinstance(each_item, list):
                print_lol(each_item)
            else:
                print(each_item)