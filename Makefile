.PHONY: debug release backend backend-dev frontend frontend-dev clean help run

debug: backend-dev frontend-dev
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

frontend:
	@echo "=== Building frontend (Release) ==="
	@cd frontend/my-react-app/ && npm install --silent
	@cd frontend/my-react-app/ && npm run build

clean:
	@echo "=== Project cleanup ==="
	@rm -rf backend/build 2>nul || true
# 	rm -rf frontend/dist
# 	rm -rf frontend/node_modules

help:
	@echo "Available commands:"
	@echo "  make		- build backend и frontend"
	@echo "  make backend	- build only backend"
	@echo "  make frontend	- build only frontend"
	@echo "  make clean	- clean build и dist"



