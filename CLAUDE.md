# CLAUDE.md — DataPersistence-JeonHyunji-10225419

## 프로젝트 개요
데이터 영속성 처리 PoC. 파일 기반(JSON 권장) 저장소에 대한 CRUD와, 프로세스 재시작 후에도 데이터가 유지되는지를 검증한다.

## 기술 스택 / 컨벤션
- C++20, Visual Studio(MSBuild, .vcxproj), gmock(NuGet)
- 코드 컨벤션은 상위 `Semiconductor` 폴더의 `CODE_CONVENTION.md`를 따른다.

## 설계 방향
- Repository 패턴으로 저장소 접근을 인터페이스(`IRepository` 등)로 추상화
- 실제 구현체는 파일(JSON) 기반으로 작성
- Create/Read/Update/Delete 각각에 대한 동작 검증

## 테스트
- Repository 인터페이스를 gmock으로 목킹하여 이를 사용하는 상위 로직을 단위 테스트한다.
- 실제 파일 I/O 동작은 별도의 통합 테스트로 검증한다(임시 파일 경로 사용).

## 빌드/실행
Visual Studio에서 솔루션을 열어 빌드/실행한다.
