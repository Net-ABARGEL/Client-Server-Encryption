import handler
from answerToClient import answer_to_client
from requestToServer import request_from_client


def case_2100(conn, uuid):
    print("Sending UUID")
    uuid_byte = uuid.encode("utf-8")
    answer = answer_to_client(2100, 32, uuid_byte)
    conn.sendall(answer)
    request = request_from_client(conn)
    handler.handle_req(request, conn)
def case_2101():
    return "Processing for Case 2101"


def case_2102():
    return "Processing for Case 2102"


def case_2103():
    return "Processing for Case 2103"


def case_2104():
    return "Processing for Case 2104"


def case_2105():
    return "Processing for Case 2105"


def case_2106():
    return "Processing for Case 2106"


def case_2107():
    return "Processing for Case 2107"


def default_case():
    return "Default Case"


