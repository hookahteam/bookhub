.PHONY: start debug release backend backend-dev frontend frontend-dev frontend-quick clean help run

start: frontend-dev

debug: backend-dev frontend-quick
	@cd backend/build/bin && ./bookhub

release: backend frontend
	@cd backend/build/bin && ./bookhub

backend-dev:
	@echo "=== Fast building backend (Debug) ==="
	@cd backend && mkdir -p build
	@cd backend/build && cmake .. -DCMAKE_BUILD_TYPE=Debug
	@cmake --build backend/build --config Debug -j4

backend:
	@echo "=== Building backend (Release) ==="
	@cd backend && mkdir build 2>nul || true
	@cd backend/build && cmake .. -DCMAKE_BUILD_TYPE=Release
	@cmake --build backend/build --config Release -j4

frontend-dev:
	@echo "=== Fast building frontend (Debug) ==="
	@cd frontend/my-react-app && npm run start

frontend-quick:
	@echo "=== Fast static frontend build (Debug) ==="
	@cd frontend/my-react-app/ && npm install --silent
	@cd frontend/my-react-app/ && \
		DISABLE_ESLINT_PLUGIN=true \
		GENERATE_SOURCEMAP=false \
		TSC_COMPILE_ON_ERROR=true \
		SKIP_PREFLIGHT_CHECK=true \
		CI=true \
		npm run build -- --no-optional

frontend:
	@echo "=== Building frontend (Release) ==="
	@cd frontend/my-react-app/ && npm install --silent
	@cd frontend/my-react-app/ && npm run build

clean:
	@echo "=== Project cleanup ==="
	@rm -rf backend/build 2>nul || true
	@rm -rf frontend/my-react-app/build
	@rm -rf frontend/my-react-app/node_modules

help:
	@echo "Available commands:"
	@echo "  make start		- frontend debugging"
	@echo "  make debug		- backend debugging"
	@echo "  make release	- build frontend and backend for release"
	@echo "  make clean		- clean build и dist"



