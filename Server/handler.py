from answers import case_2100, case_2101, case_2102, case_2103, case_2104, case_2105, case_2106, case_2107, default_case
from requests import case1025, case1026, case1027, case1028, case1029, case1030, case1031, default


def handle_req(clientrequest,conn):
    switch_dict = {
        1025: case1025,  # registration
        1026: case1026,  # send publicKey
        1027: case1027,  # reconnect
        1028: case1028,  # file sent
        1029: case1029,  # CRC correct
        1030: case1030,  # CRC error
        1031: case1031,  # CRC error forth time
    }

    selected_case = switch_dict.get(clientrequest['code'], default)
    selected_case(clientrequest, conn)


def handle_answer(value):
    switch_dict = {
        2100: case_2100,
        2101: case_2101,
        2102: case_2102,
        2103: case_2103,
        2104: case_2104,
        2105: case_2105,
        2106: case_2106,
        2107: case_2107,
    }

    case_function = switch_dict.get(value, default_case)
    return case_function()
