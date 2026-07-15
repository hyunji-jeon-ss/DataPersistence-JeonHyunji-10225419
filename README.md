# DataPersistence-JeonHyunji-10225419

반도체 시료 생산주문관리 시스템 개인과제 — **[미션1] PoC: 데이터 영속성 처리**

## 목적
**JSON 파일 기반**으로 데이터를 저장·조회하는 구조를 검증하고, CRUD 및 애플리케이션 재실행 후 데이터 유지(영속성)를 확인하는 PoC.

## 기술 스택
- C++20, Visual Studio (MSBuild, .vcxproj)
- nlohmann/json (NuGet, `nlohmann.json`) — JSON 직렬화/역직렬화
- gmock (NuGet, v1.11.0) 기반 단위 테스트

## 구조
```
DataPersistence.sln
DataPersistenceLib/       # 정적 라이브러리: Repository 및 도메인 모델
  model/Item.h             Item(id, name)
  repository/IItemRepository.h    Repository 인터페이스 (save/findById/findAll/remove)
  repository/JsonItemRepository.h/.cpp   nlohmann/json 기반 구현체
DataPersistenceApp/       # 콘솔 데모 (main.cpp), Lib 참조
DataPersistenceTest/      # gmock 기반 단위/통합 테스트, Lib 참조
```
`JsonItemRepository`는 매 호출마다 JSON 파일을 읽고 쓰는 단순한 구조이며, 생성 시 기존 파일의 최대 id를 읽어 `next_id`를 이어간다 (재실행 후에도 id가 겹치지 않도록).

## 빌드 방법 (Visual Studio)
1. `DataPersistence.sln`을 Visual Studio로 연다.
2. 처음 열면 NuGet 패키지(nlohmann.json 3.12.0, gmock 1.11.0)가 자동으로 복원된다.
   - 자동 복원이 안 되면: 솔루션 우클릭 → **NuGet 패키지 복원**
3. 구성을 **Debug / x64**로 맞춘다.
4. `Ctrl+Shift+B`로 솔루션 빌드.

## 실행 방법
- **데모 앱**: `DataPersistenceApp`을 시작 프로젝트로 설정(우클릭 → 시작 프로젝트로 설정) 후 `Ctrl+F5` 실행
  - 콘솔 메뉴에서 `1`(등록) `2`(전체 조회) `3`(단건 조회) `4`(수정) `5`(삭제) `0`(종료)을 입력하며 CRUD를 직접 조작 가능
  - 데이터는 `items.json`에 저장되며, 프로그램을 껐다 켜도 유지되는지 확인 가능
- **테스트**: `DataPersistenceTest`를 시작 프로젝트로 설정 후 `Ctrl+F5` 실행 (또는 테스트 탐색기 사용)

## 관련 문서
- 상위 저장소의 `PRD.md`, `PLAN.md` Phase 2 참고
