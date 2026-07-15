# CLAUDE.md — DataPersistence-JeonHyunji-10225419

## 프로젝트 개요
데이터 영속성 처리 PoC. **JSON 파일 기반**(nlohmann/json) 저장소에 대한 CRUD와, 프로세스 재시작 후에도 데이터가 유지되는지를 검증한다.
이 PoC에서 정한 라이브러리(nlohmann/json)와 Repository 인터페이스 사용법은 메인 프로젝트(`SampleOrderSystem`)에서도 동일하게 이어간다 (코드 자체를 그대로 재사용하지는 않음).

## 기술 스택 / 컨벤션
- C++20, Visual Studio(MSBuild, .vcxproj), gmock(NuGet)
- nlohmann/json (NuGet 패키지 `nlohmann.json`)
- 코드 컨벤션은 상위 `Semiconductor` 폴더의 `CODE_CONVENTION.md`를 따른다.

## 구조
```
DataPersistenceLib/    # 정적 라이브러리: model/Item.h, repository/(IItemRepository, JsonItemRepository)
DataPersistenceApp/    # 콘솔 CRUD 데모 (main.cpp), Lib 참조
DataPersistenceTest/   # gmock 단위/통합 테스트, Lib 참조
```

## 설계 방향
- Repository 패턴으로 저장소 접근을 인터페이스(`IItemRepository`)로 추상화 (save/findById/findAll/remove)
- 실제 구현체(`JsonItemRepository`)는 JSON 파일 기반으로 작성 (`nlohmann::json`으로 직렬화/역직렬화)
- 생성 시 기존 파일의 최대 id를 읽어 `next_id`를 이어받아, 재실행 후에도 id가 겹치지 않음
- Create/Read/Update/Delete 각각에 대한 동작 검증

## 테스트
- Repository 인터페이스를 gmock으로 목킹하여 이를 사용하는 상위 로직을 단위 테스트한다.
- 실제 파일 I/O 동작은 별도의 통합 테스트로 검증한다(임시 파일 경로 사용).

## 한글 인코딩 (중요)
콘솔에 한글을 출력하므로 반드시 아래 두 가지를 유지한다. 자세한 이유는 상위 `Semiconductor` 폴더의 `CLAUDE.md` 참고.
1. 모든 `.vcxproj`의 각 ClCompile 설정에 `<AdditionalOptions>/utf-8 %(AdditionalOptions)</AdditionalOptions>` 적용
2. 콘솔 진입점(main)에서 `SetConsoleOutputCP(CP_UTF8)` / `SetConsoleCP(CP_UTF8)` 호출

`<windows.h>`를 include하는 파일에서 `std::numeric_limits<T>::max()` 등을 함께 쓸 경우, include 전에 `#define NOMINMAX`를 반드시 추가한다 (`windows.h`의 `max`/`min` 매크로와 충돌해 컴파일 에러 발생).

## 커밋 컨벤션
`COMMIT_CONVENTION.md`를 따른다. 커밋 메시지는 `<헤더> 변경 내용` 형식이며, 헤더는 `<FEATURE>`/`<FIX>`/`<DOCS>`/`<STYLE>`/`<REFACTOR>`/`<TEST>`/`<CHORE>` 중 하나만 사용한다.

## 빌드/실행
Visual Studio에서 솔루션을 열어 빌드/실행한다. **빌드가 실패한 상태에서는 절대 커밋하지 않는다** — 반드시 로컬 빌드 성공(및 가능하면 테스트 통과)을 확인한 뒤 커밋한다. 자세한 내용은 상위 `Semiconductor` 폴더의 `CLAUDE.md` 참고.
