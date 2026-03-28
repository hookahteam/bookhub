.PHONY: all backend frontend clean help run

run: backend frontend
	@cd backend/build/bin && ./bookhub

backend:
	@echo "=== Building backend ==="
	@cd backend && mkdir build 2>nul || true
	@cd backend/build && cmake .. -DCMAKE_BUILD_TYPE=Release
	@cmake --build backend/build --config Release -j4

frontend:
	@echo "=== Building frontend ==="
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



