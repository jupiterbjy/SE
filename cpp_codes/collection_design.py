from typing import List


class User:
    def __init__(self, id_: str, pw: str):
        """유저

        Args:
            id_: 로그인 ID
            pw: 로그인 비번
        """
        self.id = id_
        self.pw = pw


class CompanyUser(User):
    def __init__(self, id_: str, pw: str, company_name: str, business_num: str):
        """회사 회원

        Args:
            id_: 로그인 ID
            pw: 로그인 비번
            company_name: 회사 이름
            business_num: 사업자 번호
        """
        super().__init__(id_, pw)

        self.company_name = company_name
        self.business_num = business_num


class CommonUser(User):
    def __init__(self, id_: str, pw: str, name: str, ssn: str):
        """일반 회원

        Args:
            id_: 로그인 ID
            pw: 로그인 비번
            name: 이름
            ssn: 주민 번호 (Social Security Number)
        """
        super().__init__(id_, pw)

        self.name = name
        self.ssn = ssn


class UserCollection:
    def __init__(self):
        """회원 콜렉션
        전혀 파이썬 스럽지 않지만, C++ 에 가깝게 배열 형태로 사용
        """
        self.users: List[User | None] = [None] * 100
        self.total_users = 0

    def _find_user_index_by_id(self, id_: str) -> int:
        """private 함수, 유저 ID를 찾아 배열 내 Index 반환. 없을시 -1

        Args:
            id_: 유저 로그인 ID

        Returns:
            배열 내 유저의 인덱스
        """

        for idx in range(self.total_users):
            if self.users[idx].id == id_:
                return idx

        # 없을시 -1
        return -1

    def does_user_exist(self, id_: str) -> bool:
        """유저 존재 여부 확인. 존재시 참, 없을시 거짓"""

        return self._find_user_index_by_id(id_) != -1

    def add_user(self, user: User) -> None:
        """새 유져 추가. C++ 구현시 self.total_users++ 로 후위 연산자 사용할 것

        Args:
            user: 유저 객체

        Returns:
            그런거 없음
        """

        self.users[self.total_users] = user
        self.total_users += 1

    def del_user(self, id_: str) -> None:
        """유져 삭제. 유저 없는 경우는 상정하지 않음

        Args:
            id_: 유저 로그인 ID

        Returns:
            그런거 없음
        """

        user_idx = self._find_user_index_by_id(id_)

        # 정석적 C++ 삭제법 기억 안남. 일단 이렇게
        user = self.users[user_idx]
        del user

        # user_idx + 1부터 끝까지 유저 땡겨옴
        for idx in range(user_idx, self.total_users - 1):
            self.users[idx] = self.users[idx + 1]

        self.total_users -= 1

    def get_user_by_id(self, id_: str) -> User:
        """로그인 ID로 유저 정보 획득

        Args:
            id_: 유저 로그인 ID

        Returns:
            유저 객체
        """

        return self.users[self._find_user_index_by_id(id_)]

    def get_user_count(self) -> int:
        """C++ for 문 순회 목적 으로 전체 유저 수 반환"""

        return self.total_users


class AllUsers:
    def __init__(self, company_collection, common_collection):
        self.company_collection = UserCollection()
        self.common_collection = UserCollection()

    def add_company_user(self, id_: str, pw: str, company_name: str, business_num: str):
        """새 회사 회원 추가"""

        new_user = CompanyUser(id_, pw, company_name, business_num)
        self.company_collection.add_user(new_user)

    def add_common_user(self, id_: str, pw: str, name: str, ssn: str):
        """새 회사 회원 추가"""

        new_user = CommonUser(id_, pw, name, ssn)
        self.company_collection.add_user(new_user)

    def delete_user_by_id(self, id_: str) -> None:
        """로그인 ID로 유저 삭제

        Args:
            id_: 로그인 ID

        Returns:
            그런거 없음
        """

        if self.company_collection.does_user_exist(id_):
            self.company_collection.del_user(id_)
        else:
            self.common_collection.del_user(id_)
