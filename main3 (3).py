

def create_matrix():
    G = nx.grid_2d_graph(17, 17)
    pos = {(x, y): (x, y) for x, y in G.nodes()}
    H = nx.grid_2d_graph(15, 15)
    mapping = {(x, y): (x + 1, y + 1) for x, y in H.nodes()}  # old labels as keys and new labels as values
    H = nx.relabel_nodes(H, mapping)
    G.remove_nodes_from(H.nodes())
    mapping = {(x, y): (2 * x, 2 * y) for x, y in G.nodes()}  # old labels as keys and new labels as values
    G = nx.relabel_nodes(G, mapping)
    pos = {(x, y): (x, y) for x, y in G.nodes()}

    for j in range(16):
        for i in range(16):
            G.add_node(((2 * i) + 1, (2 * j) + 1))
            node_pos = {((2 * i) + 1, (2 * j) + 1): ((2 * i) + 1, (2 * j) + 1)}  # mid
            pos.update(node_pos)

            G.add_node(((2 * i) + 1, (2 * j) + 2))
            node_pos = {((2 * i) + 1, (2 * j) + 2): ((2 * i) + 1, (2 * j) + 2)}  # top
            pos.update(node_pos)

            G.add_node(((2 * i), (2 * j) + 1))
            node_pos = {((2 * i), (2 * j) + 1): ((2 * i), (2 * j) + 1)}  # left mid
            pos.update(node_pos)

            G.add_edge(((2 * i) + 1, (2 * j) + 1), ((2 * i) + 1, (2 * j) + 2), edge_type="y_switch")  # mid to top
            G.add_edge(((2 * i) + 1, (2 * j) + 1), ((2 * i), (2 * j) + 1), edge_type="x_switch")  # mid to left mid
            G.add_edge(((2 * i) + 1, (2 * j) + 2), ((2 * i), (2 * j) + 1), edge_type="bypass_switch")  # top to left mid

    for j in range(16):
        for i in range(15):
            G.add_edge(((2 * i) + 1, (2 * j) + 2), ((2 * i) + 3, (2 * j) + 2), edge_type="rail")

    for i in range(16):
        for j in range(15):
            G.add_edge(((2 * i), (2 * j) + 1), ((2 * i), (2 * j) + 3), edge_type="rail")

    for i in range(17):  # 0-30
        G.remove_node((i * 2, 0))

    for j in range(16):  # 0-30
        G.remove_node((32, (j * 2) + 2))

    for j in range(16):  # 0-30
        G.remove_node((0, (j * 2) + 2))

    for i in range(15):  # 0-30
        G.remove_node(((i * 2) + 2, 32))
    return G


G = create_matrix()


def convert_to_G_Coord(source_x,source_y,destination_x,destination_y):
    source_x = (source_x*2)+1
    source_y = (source_y*2)+1
    destination_x = (destination_x*2)+1
    destination_y = (destination_y*2)+1

    source_z = source_x
    source_x = source_y
    source_y = source_z

    destination_z = destination_x
    destination_x = destination_y
    destination_y = destination_z
    return source_x,source_y,destination_x,destination_y

#ONLY FOR SINGLE SOURCE/DESTINATION!!!!!!!!!!!!!!!!!!!!!!!!!!!

source_x = 0
source_y = 0
destination_x = 5
destination_y = 8

source_x,source_y,destination_x,destination_y = convert_to_G_Coord(source_x,source_y,destination_x,destination_y)

length,path=nx.bidirectional_dijkstra(G,(source_x,source_y),(destination_x,destination_y))

#ONLY FOR SINGLE SOURCE/DESTINATION!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ONLY FOR multi source/destination!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

# source_x = 0
# source_y = 0
# destination_x = 3
# destination_y = 5
#
# source1_x = 6
# source1_y = 2
# destination1_x = 6
# destination1_y = 6
#
# source_x,source_y,destination_x,destination_y = convert_to_G_Coord(source_x,source_y,destination_x,destination_y)
# source1_x,source1_y,destination1_x,destination1_y = convert_to_G_Coord(source1_x,source1_y,destination1_x,destination1_y)
#
# length,path=nx.bidirectional_dijkstra(G,(source_x,source_y),(destination_x,destination_y))
# for i in range (len(path)-1):
#     G.remove_edge(path[i],path[i+1])
# try:
#     length1,path1=nx.bidirectional_dijkstra(G,(source1_x,source1_y),(destination1_x,destination1_y))
# except ValueError:
#     G = create_matrix()
#     length1,path1=nx.bidirectional_dijkstra(G,(source1_x,source1_y),(destination1_x,destination1_y))
#     for i in range (len(path1)-1):
#         G.remove_edge(path1[i],path1[i+1])
#     length,path=nx.bidirectional_dijkstra(G,(source_x,source_y),(destination_x,destination_y))
# G = create_matrix()
#ONLY FOR multi source/destination!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


def get_switches(path):
    switch_list = []
    for i in range (len(path)-1):
        edge_data = G.get_edge_data(path[i],path[i+1])
        switch = []
        if (edge_data["edge_type"] == "x_switch"):
            y = path[i][1]
            x1 = path[i][0]
            x2 = path[i+1][0]
            if x1>x2:
                x = x1
            else:
                x = x2
            x = (x-1)/2
            y = (y-1)/2
            z = x
            x = y
            y = z
            x = int(x)
            y = int(y)
            switch = [x,y,1,0]
            switch_list.append(switch)
            #only difference between nodes is x coord, just need to use node with bigger x coord
        elif (edge_data["edge_type"] == "y_switch"):
            x = path[i][0]
            y1 = path[i][1]
            y2 = path[i+1][1]
            if y1>y2:
                y = y2
            else:
                y = y1
            x = (x-1)/2
            y = (y-1)/2
            z = x
            x = y
            y = z
            x = int(x)
            y = int(y)
            switch = [x,y,2,0]
            switch_list.append(switch)
            #only difference between nodes is y coord, just need to use node with smaller y coord
        elif (edge_data["edge_type"] == "bypass_switch"):
            x1 = path[i][0]
            x2 = path[i+1][0]
            y1 = path[i][1]
            y2 = path[i+1][1]
            if x1>x2:
                x = x1
            else:
                x = x2
            if y1>y2:
                y = y2
            else:
                y = y1
            x = (x-1)/2
            y = (y-1)/2
            z = x
            x = y
            y = z
            x = int(x)
            y = int(y)
            switch = [x,y,3,0]
            switch_list.append(switch)
    return switch_list


switch_list_total = get_switches(path)


#ONLY FOR multi source/destination!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# new_switches = get_switches(path1)
#
# switch_list_total = switch_list_total + new_switches
#ONLY FOR multi source/destination!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



#have switch_list at this point, now iterate through it to send off 1 switch at a time

arduino = serial.Serial(port='COM5', baudrate=115200, timeout=None)  # parity=serial.PARITY_EVEN, stopbits=serial.STOPBITS_TWO)

# pt1 = "{},{},{}\n".format(0, 0, 1)
# pt2 = "{:02}{:02}{:01}{:01}".format(1, 0, 1, 0)
# pt3 = "{:02}{:02}{:01}{:01}".format(0, 1, 2, 1)

time.sleep(5)

# arduino.write(bytes("33", 'utf-8'))
# time.sleep(dy)

# arduino.write(bytes("{},{},{},{}\n".format(0, 4, 2, 0), 'utf-8'))
# time.sleep(dy)

# arduino.write(bytes("{},{},{},{}\n".format(0, 5, 2, 0), 'utf-8'))
# time.sleep(dy)

# arduino.write(bytes("{},{},{},{}\n".format(0, 4, 2, 0), 'utf-8'))
# time.sleep(dy)


dy=0.001  # actual freq of sending commands is 60Hz, setting dy this low ensures max speed will be used (60hz)

# FOR BATCH BASED!!!!!!!
# switch_list_len = len(switch_list_total)
# arduino.write(bytes("{}\n".format(switch_list_len), 'utf-8'))
# time.sleep(dy)
# FOR BATCH BASED!!!!!!!

for i in range(len(switch_list_total)):
    # arduino.write(bytes("{},{},{},{}\n".format(0, 0, 1,1), 'utf-8'))
    # time.sleep(dy)
    arduino.write(bytes("{},{},{},{}\n".format(switch_list_total[i][0], switch_list_total[i][1], switch_list_total[i][2], switch_list_total[i][3]), 'utf-8'))
    time.sleep(dy)




# arduino.write(bytes("{},{},{},{}\n".format(0, 0, 1, 0), 'utf-8'))
# time.sleep(dy)
# arduino.write(bytes("{},{},{},{}\n".format(1, 0, 1, 0), 'utf-8'))
# time.sleep(dy)

# for i in range(10):
#     # arduino.write(bytes("{},{},{},{}\n".format(0, 0, 1,1), 'utf-8'))
#     # time.sleep(dy)
#     arduino.write(bytes("{},{},{},{}\n".format(0, 4, 2, 0), 'utf-8'))
#     time.sleep(dy)
#     arduino.write(bytes("{},{},{},{}\n".format(0, 4, 2, 1), 'utf-8'))
#     time.sleep(dy)

# arduino.write(bytes("{},{},{},{}\n".format(0, 0, 1, 0), 'utf-8'))
# time.sleep(dy)
# arduino.write(bytes("{},{},{},{}\n".format(1, 0, 1, 0), 'utf-8'))
#time.sleep(3*dy)

# for i in range(5):
    # arduino.write(bytes("{},{},{},{}\n".format(0, 0, 1,1), 'utf-8'))
    # time.sleep(dy)
    # arduino.write(bytes("{},{},{},{}\n".format(0, 0, 1, 0), 'utf-8'))
    # time.sleep(dy)
    # arduino.write(bytes("{},{},{},{}\n".format(0, 0, 1, 1), 'utf-8'))
    # time.sleep(dy)

# arduino.write(bytes("{},{},{},{}\n".format(0, 4, 2, 0), 'utf-8'))
# time.sleep(dy)

# arduino.write(bytes("{},{},{},{}\n".format(0, 5, 2, 0), 'utf-8'))
#time.sleep(dy*3)

# for i in range(5):
#     # arduino.write(bytes("{},{},{},{}\n".format(0, 0, 1,1), 'utf-8'))
#     # time.sleep(dy)
#     arduino.write(bytes("{},{},{},{}\n".format(0, 4, 2, 0), 'utf-8'))
#     time.sleep(dy)
#     arduino.write(bytes("{},{},{},{}\n".format(0, 4, 2, 1), 'utf-8'))
#     time.sleep(dy)
#
# arduino.write(bytes("{},{},{},{}\n".format(1, 0, 1, 1), 'utf-8'))

# time.sleep(1)
# arduino.write(bytes(pt2, 'utf-8'))
# time.sleep(1)
# arduino.write(bytes(pt3, 'utf-8'))


# list_size = len(list_of_lists)
# list_size = str(list_size)
# for sublist in list_of_lists:
#     x_num = sublist[0]
#     arduino.write(bytes(str(x_num), 'utf-8'))
#     time.sleep(delay)
#     y_num = sublist[1]
#     arduino.write(bytes(str(y_num), 'utf-8'))
#     time.sleep(delay)
#     sw = sublist[2]
#     arduino.write(bytes(str(sw), 'utf-8'))
#     time.sleep(delay)
#     c = sublist[3]
#     arduino.write(bytes(str(c), 'utf-8'))
#     time.sleep(delay)
# y_num = input("Enter y: ")  # Taking input from user
# y_num = "{:2}".format(y_num)
# arduino.write(bytes(y_num, 'utf-8'))
# time.sleep(delay)
#
# data = arduino.readline()
# if len(data) > 0:
#     print(data)




# while True:
#     x_num = input("Enter x: ")  # Taking input from user
#     x_num = "{:2}".format(x_num)
#     value = write_read(x_num)
#     print(value)  # printing the value
#
#     y_num = input("Enter y: ")  # Taking input from user
#     y_num = "{:2}".format(y_num)
#     value = write_read(y_num)
#     print(value)  # printing the value
#
#     sw = input("Enter sw: ")  # Taking input from user
#     sw = "{:1}".format(sw)
#     value = write_read(sw)
#     print(value)  # printing the value
#
#     c = input("Enter c: ")  # Taking input from user
#     c = "{:1}".format(c)
#     value = write_read(c)
#     print(value)  # printing the value

# def print_hi(name):
# Use a breakpoint in the code line below to debug your script.
# print(f'Hi, {name}')  # Press Ctrl+F8 to toggle the breakpoint.


# Press the green button in the gutter to run the script.
# if __name__ == '__main__':
#     print_hi('PyCharm')

# See PyCharm help at https://www.jetbrains.com/help/pycharm/