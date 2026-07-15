# DataPersistence-JeonHyunji-10225419

반도체 시료 생산주문관리 시스템 개인과제 — **[미션1] PoC: 데이터 영속성 처리**

## 목적
**JSON 파일 기반**으로 데이터를 저장·조회하는 구조를 검증하고, CRUD 및 애플리케이션 재실행 후 데이터 유지(영속성)를 확인하는 PoC.

## 기술 스택
- C++20, Visual Studio (MSBuild, .vcxproj)
- nlohmann/json (NuGet, `nlohmann.json`) — JSON 직렬화/역직렬화
- gmock (NuGet, v1.11.0) 기반 단위 테스트

## 관련 문서
- 상위 저장소의 `PRD.md`, `PLAN.md` Phase 2 참고
